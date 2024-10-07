/*
 * Copyright (C) 2016-2022 Konstantin Polevik
 * All rights reserved
 *
 * This file is part of the Minibook. Redistribution and use in source and
 * binary forms, with or without modification, are permitted exclusively
 * under the terms of the MIT license. You should have received a copy of the
 * license with this file. If not, please visit:
 * https://github.com/out61h/minibook/blob/main/LICENSE
 */
#include "Typesetter.hpp"

#include <Constants/Chars.hpp>
#include <Interfaces/Font.hpp>
#include <Structures/Params.hpp>

using namespace Minibook;

Typesetter::Typesetter( WordStream& source, Font& font, const Params& params )
    : m_source( source )
    , m_font( font )
    , m_justification( params.Line.Justification )
    , m_spaceWidth( m_font.CreateGlyph( Chars::kSpace ).Width ) // TODO: GetGlyphWidth() ?
    , m_maxLineWidth( params.Page.Size.Width - params.Page.Margin.Left - params.Page.Margin.Right )
    , m_lineSpacing( params.Font.Size * params.Line.Spacing )
    , m_paragraphSpacing( params.Font.Size * params.Paragraph.Spacing )
    , m_paragraphIndent( m_spaceWidth * params.Paragraph.Indent )
    , m_syllableLastChar( L'\0' )
    , m_startNewParagraph( true )
{
}

Line Typesetter::Fetch()
{
    Line line;
    line.SetHeight( m_lineSpacing );

    // Add indent at the beginning of a new paragraph.
    if ( m_startNewParagraph )
    {
        line.AppendGlyph( Glyph( Chars::kTabulation, m_paragraphIndent ) );
        m_startNewParagraph = false;
    }

    wchar_t lineLastChar = L'\0';

    for ( ;; )
    {
        // Get next portion of the text.
        if ( m_syllable.empty() )
        {
            // XXX: NO WS, LF should be on next line?
            // Text := LineFeed | Syllable LineFeed | Syllable SoftHypen | Syllable
            m_syllable = m_source.Fetch();
            m_syllableLastChar = L'\0';

            if ( m_syllable.empty() )
                break;

            m_syllableLastChar = m_syllable.back();

            // Drop control symbols, separators and punctuation marks.
            switch ( m_syllableLastChar )
            {
            case Chars::kLineFeed:
            case Chars::kSoftHyphen:
                m_syllable.pop_back();
                break;
            default:
                break;
            }
        }

        // making text layout
        Line chunk;
            // TODO: Should forcibly cut the text line if we can't fully type with hyphens
        for ( const wchar_t ch : m_syllable )
            chunk.AppendGlyph( m_font.CreateGlyph( ch ) );

        // check total length
        const double lineWidth = line.GetWidth() + chunk.GetWidth();

        // Line overflow check.
        // TODO: If the line cannot be split, we attach it as a whole, but we need to force it to
        // be split into parts.
        if ( lineWidth > m_maxLineWidth
             && !( chunk.GetWidth() > m_maxLineWidth && line.IsEmpty() ) )
        {
            break;
        }

        // Transfer part of the text to the line

        if ( lineLastChar && lineLastChar != Chars::kSoftHyphen )
            line.AppendGlyph( m_font.CreateGlyph( Chars::kSpace ) );

        line.AppendLine( chunk );
        lineLastChar = m_syllableLastChar;

        m_syllable.clear();
        m_syllableLastChar = L'\0';

        // Beginning of a new paragraph - give the typed line
        if ( lineLastChar == Chars::kLineFeed )
        {
            m_startNewParagraph = true;
            line.SetHeight( m_lineSpacing + m_paragraphSpacing );
            break;
        }
    }

    if ( lineLastChar == Chars::kSoftHyphen )
        line.AppendGlyph( m_font.CreateGlyph( Chars::kSoftHyphen ) );

    // Optional text justification.
    if ( m_justification )
    {
        // FIXME: do not align incomplete line.
        // Do not align last line of a paragraph.
        if ( !m_startNewParagraph )
            line.JustifyGlyphs( m_maxLineWidth );
    }

    return line;
}

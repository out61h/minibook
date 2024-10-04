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
    , m_spaceWith( m_font.CreateGlyph( Chars::kSpace ).Width )
    , m_lineWidth( params.Page.Size.Width - params.Page.Margin.Left - params.Page.Margin.Right )
    , m_lineSpacing( params.Font.Size * params.Line.Spacing )
    , m_paragraphSpacing( params.Font.Size * params.Paragraph.Spacing )
    , m_paragraphIndent( m_spaceWith * params.Paragraph.Indent )
    , m_startNewParagraph( true )
{
}

Line Typesetter::Fetch()
{
    Line result;

    result.SetHeight( m_lineSpacing );

    // Add an indent at a new paragraph start
    if ( m_startNewParagraph )
    {
        result.Append( Glyph( Chars::kTabulation, m_paragraphIndent ) );
        m_startNewParagraph = false;
    }

    for ( ;; )
    {
        // get the next portion of the text
        if ( m_text.empty() )
        {
            // Text := Lexeme SoftHypen | Lexeme WhiteSpace | Lexeme LineFeed | LineFeed
            m_text = m_source.Fetch();

            if ( m_text.empty() )
                break;
        }

        // making text layout
        Line chunk;
        {
            // TODO: Should forcibly cut the text line if we can't fully type with hyphens
            for ( const wchar_t letter : m_text )
            {
                Glyph glyph = ( letter != Chars::kLineFeed ) ? m_font.CreateGlyph( letter )
                                                             : Glyph( Chars::kLineFeed, nullptr );

                chunk.Append( glyph );
            }
        }

        // check total length
        const double resultWidth
            = result.GetWidth()
              - ( result.IsEndsWith( Chars::kSoftHyphen ) ? result.GetLast().Width : 0. );

        const double chunkWith
            = chunk.GetWidth() - ( chunk.IsEndsWith( Chars::kSpace ) ? chunk.GetLast().Width : 0. );

        const double lineWidth = resultWidth + chunkWith - m_spaceWith / 2.0;

        // Line overflow check.
        // If the line cannot be split, we attach it as a whole, but we need to force it to be split
        // into parts
        if ( lineWidth > m_lineWidth && !( chunk.GetWidth() > m_lineWidth && result.IsEmpty() ) )
        {
            // Remove the last invisible character from a string
            if ( result.IsEndsWith( Chars::kSpace ) )
                result.RemoveLast();

            break;
        }

        // Transfer part of the text to the line
        {
            m_text.clear();

            // If the last character is a soft hyphen, then remove it before appending a new portion
            // of the text
            if ( result.IsEndsWith( Chars::kSoftHyphen ) )
                result.RemoveLast();

            result.Append( chunk );
        }

        // Beginning of a new paragraph - give the typed line
        if ( result.IsEndsWith( Chars::kLineFeed ) )
        {
            m_startNewParagraph = true;
            result.SetHeight( m_lineSpacing + m_paragraphSpacing );
            break;
        }
    }

    // Optional text justification
    if ( !m_startNewParagraph && m_justification )
        result.Justify( m_lineWidth );

    return result;
}

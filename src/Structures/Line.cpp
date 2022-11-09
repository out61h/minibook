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
#include "Line.hpp"

#include <Constants/Chars.hpp>

using namespace Minibook;

void Line::Append( const Glyph& glyph )
{
    m_glyphs.push_back( glyph );
    m_width += glyph.Width;
}

void Line::Append( const Line& glyphs )
{
    m_glyphs.insert( m_glyphs.end(), glyphs.m_glyphs.begin(), glyphs.m_glyphs.end() );
    m_width += glyphs.GetWidth();
}

void Line::RemoveLast()
{
    if ( !m_glyphs.empty() )
    {
        m_width -= m_glyphs.back().Width;
        m_glyphs.pop_back();
    }
}

const Glyph Line::GetLast() const
{
    return m_glyphs.back();
}

bool Line::IsEndsWith( wchar_t ch ) const
{
    return !m_glyphs.empty() && m_glyphs.back().Index == ch;
}

double Line::GetWidth() const
{
    return m_width;
}

double Line::GetHeight() const
{
    return m_height;
}

bool Line::IsEmpty() const
{
    return m_glyphs.empty();
}

void Line::Justify( double lineWidth )
{
    size_t spaceCount = 0;
    double glyphsWidth = 0;

    for ( const auto& glyph : m_glyphs )
    {
        if ( glyph.Index == Chars::kSpace )
        {
            spaceCount++;
        }
        else
        {
            glyphsWidth += glyph.Width;
        }
    }

    if ( spaceCount )
    {
        const double spaceWidth = ( lineWidth - glyphsWidth ) / (double)spaceCount;

        for ( auto& glyph : m_glyphs )
        {
            if ( glyph.Index == Chars::kSpace )
                glyph.Width = spaceWidth;
        }
    }
}

size_t Line::GetSize() const
{
    return m_glyphs.size();
}

const Glyph& Line::operator[]( size_t index ) const
{
    return m_glyphs[index];
}

void Line::SetHeight( double height )
{
    m_height = height;
}
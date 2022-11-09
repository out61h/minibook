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
#include "Printer.hpp"

#include <Interfaces/Font.hpp>
#include <Structures/Line.hpp>

#include <cassert>

using namespace Minibook;

Printer::Printer( const Params& params, Font& font, Stream<Line>& source )
    : m_params( params )
    , m_font( font )
    , m_page( params.Page.Size.Width, params.Page.Size.Height, params.Page.Gamma )
    , m_source( source )
{
}

const Page* Printer::Fetch()
{
    m_page.Clear( m_params.Page.Color );

    double linePosition = m_params.Page.Size.Height - m_params.Page.Margin.Top;
    size_t lineCount = 0;

    for ( ;; ++lineCount )
    {
        Line line = m_source.Fetch();

        if ( line.IsEmpty() )
            break;

        m_font.BeginDraw();

        double x = m_params.Page.Margin.Left;
        double y = linePosition;

        for ( size_t i = 0; i < line.GetSize(); ++i )
        {
            std::tie( x, y ) = m_font.DrawGlyph( m_page, line[i], x, y, m_params.Font.Color );

            // forcibly trim the line if it doesn't fit
            if ( x > m_params.Page.Size.Width )
                break;
        }

        linePosition -= line.GetHeight();

        if ( linePosition <= m_params.Page.Margin.Bottom )
            break;
    }

    return lineCount ? &m_page : nullptr;
}

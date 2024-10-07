/*
 * Copyright (C) 2016-2024 Konstantin Polevik
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

#include <tuple>

using namespace Minibook;

Printer::Printer( LineStream& source, Font& font, const Params& params )
    : m_source( source )
    , m_font( font )
    , m_params( params )
    , m_page( params.Page.Size.Width, params.Page.Size.Height, params.Page.Gamma )
{
}

const Page* Printer::Fetch()
{
    m_page.Clear( m_params.Page.Color );

    const double pageRightMarginX = m_params.Page.Size.Width;
    const double pageBottomMarginY = m_params.Page.Margin.Bottom;
    const double linePosX = m_params.Page.Margin.Left;

    double linePosY = m_params.Page.Size.Height - m_params.Page.Margin.Top;
    size_t lineCount = 0;

    for ( ;; ++lineCount )
    {
        const Line line = m_source.Fetch();

        if ( line.IsEmpty() )
            break;

        m_font.ResetLastPrintedGlyph();

        double x = linePosX;
        double y = linePosY;

        for ( size_t i = 0; i < line.GetGlyphCount(); ++i )
        {
            std::tie( x, y ) = m_font.PrintGlyph( m_page, line[i], x, y, m_params.Font.Color );

            // forcibly trim the line if it doesn't fit
            if ( x > pageRightMarginX )
                break;
        }

        linePosY -= line.GetHeight();

        if ( linePosY <= pageBottomMarginY )
            break;
    }

    return lineCount ? &m_page : nullptr;
}

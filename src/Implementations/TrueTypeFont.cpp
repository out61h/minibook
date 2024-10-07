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
#include "TrueTypeFont.hpp"

#include <Exceptions/FileNotOpened.hpp>
#include <Structures/Page.hpp>

#include <agg_renderer_scanline.h>

#include <cassert>

using namespace Minibook;

namespace
{
    agg::rgba ToAgg( const Color& color )
    {
        return { color.red, color.green, color.blue, color.alpha };
    }
} // namespace

TrueTypeFont::TrueTypeFont( const std::filesystem::path& fontFile, double size, bool hinting )
    : m_cache( m_engine )
{
    if ( !m_engine.load_font( fontFile.generic_string().c_str(), 0, agg::glyph_ren_agg_gray8 ) )
        throw Exceptions::FileNotOpened( fontFile.generic_string() );

    m_engine.hinting( hinting );
    m_engine.height( size );
    m_engine.width( size );
    m_engine.flip_y( false );
    m_engine.gamma( agg::gamma_none() );
}

Glyph TrueTypeFont::CreateGlyph( wchar_t ch )
{
    return Glyph( ch, m_cache.glyph( ch ) );
}

std::pair<double, double>
TrueTypeFont::PrintGlyph( Page& page, const Glyph& glyph, double x, double y, const Color& color )
{
    if ( glyph.Cache )
    {
        const agg::glyph_cache* g = glyph.Cache; // m_cache.glyph( glyph.Index );
        m_cache.add_kerning( &x, &y );
        m_cache.init_embedded_adaptors( g, x, y );
        assert( g->data_type == agg::glyph_data_gray8 );

        auto& renderer = page.GetRenderer();

        renderer.color( ToAgg( color ) );
        agg::render_scanlines( m_cache.gray8_adaptor(), m_cache.gray8_scanline(), renderer );

        y += g->advance_y;
    }

    x += glyph.Width;

    return { x, y };
}

void TrueTypeFont::ResetLastPrintedGlyph()
{
    m_cache.reset_last_glyph();
}

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
#include "Page.hpp"

#include <cassert>

using namespace Minibook;

Page::Page( int width, int height, double gamma )
    : m_width( width )
    , m_height( height )
    , m_pixels{ new agg::int8u[width * height * 4] }
    , m_buff( m_pixels.get(), width * 4, height, -width * 3 )
    , m_format( m_buff, m_gammaLut )
    , m_renderer( m_format )
    , m_rendererImpl( m_renderer )
{
    assert( width > 0 && height > 0 );

    m_gammaLut.gamma( gamma );
}

int Page::GetWidth() const
{
    return m_width;
}

int Page::GetHeight() const
{
    return m_height;
}

const uint8_t* Page::GetBuffer() const
{
    return m_pixels.get();
}

uint8_t Page::operator()( int col, int row ) const
{
    assert( col >= 0 && col < m_width );
    assert( row >= 0 && row < m_height );

    return m_buff.row_ptr( m_height - 1 - row )[col * 3];
}

void Page::Clear( const Color& color )
{
    m_renderer.clear( color );
}

Page::RendererImplementation& Page::GetRenderer()
{
    return m_rendererImpl;
}

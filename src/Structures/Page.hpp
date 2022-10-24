#pragma once

#include <Structures/Color.hpp>

#include <agg_basics.h>
#include <agg_gamma_lut.h>
#include <agg_pixfmt_rgb.h>
#include <agg_renderer_base.h>
#include <agg_renderer_scanline.h>
#include <agg_rendering_buffer.h>

#include <cstdint>
#include <memory>

namespace Minibook
{
    class Page final
    {
    public:
        using GammaLut = agg::gamma_lut<agg::int8u, agg::int16u, 8, 16>;
        // TODO: greyscale 8 bit
        using PixelFormat = agg::pixfmt_bgr24_gamma<GammaLut>;
        using Renderer = agg::renderer_base<PixelFormat>;
        using RendererAntiAlias = agg::renderer_scanline_aa_solid<Renderer>;
        using RendererBinary = agg::renderer_scanline_bin_solid<Renderer>;
        using RendererImplementation = RendererAntiAlias;

        Page( int width, int height, double gamma );

        int GetWidth() const;
        int GetHeight() const;
        const uint8_t* GetBuffer() const;

        uint8_t operator()( int col, int row ) const;

        void Clear( const Color& color );

        RendererImplementation& GetRenderer();

    private:
        int m_width;
        int m_height;
        std::unique_ptr<agg::int8u[]> m_pixels;
        agg::row_accessor<agg::int8u> m_buff;

        GammaLut m_gammaLut;
        PixelFormat m_format;
        Renderer m_renderer;
        RendererImplementation m_rendererImpl;
    };
} // namespace Minibook

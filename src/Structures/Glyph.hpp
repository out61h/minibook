#pragma once

#include <agg_font_cache_manager.h>

namespace Minibook
{
    struct Glyph
    {
        Glyph()
            : Index( 0 )
            , Cache( nullptr )
            , Width( 0 )
        {
        }

        Glyph( wchar_t ch, double width )
            : Index( ch )
            , Cache( nullptr )
            , Width( width )
        {
        }

        Glyph( wchar_t ch, const agg::glyph_cache* glyph )
            : Index( ch )
            , Cache( glyph )
            , Width( glyph ? glyph->advance_x : 0 )
        {
        }

        wchar_t Index;
        const agg::glyph_cache* Cache;
        double Width;
    };
} // namespace Minibook

#pragma once

#include <Interfaces/Font.hpp>

#include <agg_font_cache_manager.h>
#include <agg_font_freetype.h>

#include <string>

namespace Minibook
{
    class TrueTypeFont final : public Font
    {
    public:
        TrueTypeFont( std::string_view filename, double size, bool hinting );

        virtual Glyph CreateGlyph( wchar_t ch ) override;

        virtual std::pair<double, double>
        DrawGlyph( Page& page, const Glyph& glyph, double x, double y, Color color ) override;

        virtual void BeginDraw() override;

    private:
        using FontEngine = agg::font_engine_freetype_int32;
        using FontCache = agg::font_cache_manager<FontEngine>;

        FontEngine m_engine;
        FontCache m_cache;
    };
} // namespace Minibook

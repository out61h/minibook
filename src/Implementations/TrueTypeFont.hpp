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
#pragma once

#include <Interfaces/Font.hpp>

#include <agg_font_cache_manager.h>
#include <agg_font_freetype.h>

#include <filesystem>
#include <string>

namespace Minibook
{
    class TrueTypeFont final : public Font
    {
    public:
        TrueTypeFont( const std::filesystem::path& fontFile, double size, bool hinting );

        Glyph CreateGlyph( wchar_t ch ) override;

        std::pair<double, double> PrintGlyph( Page& page,
                                              const Glyph& glyph,
                                              double x,
                                              double y,
                                              const Color& color ) override;

        void ResetLastPrintedGlyph() override;

    private:
        using FontEngine = agg::font_engine_freetype_int32;
        using FontCache = agg::font_cache_manager<FontEngine>;

        FontEngine m_engine;
        FontCache m_cache;
    };
} // namespace Minibook

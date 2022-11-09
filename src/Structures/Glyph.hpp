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

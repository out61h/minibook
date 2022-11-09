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

#include <Structures/Color.hpp>
#include <Structures/Glyph.hpp>

#include <utility>

namespace Minibook
{
    class Page;

    class Font
    {
    public:
        virtual Glyph CreateGlyph( wchar_t ch ) = 0;

        virtual void BeginDraw() = 0;

        virtual std::pair<double, double>
        DrawGlyph( Page& page, const Glyph& glyph, double x, double y, Color color ) = 0;

        virtual ~Font() = default;
    };
} // namespace Minibook

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

#include <Structures/Glyph.hpp>

#include <utility>

namespace Minibook
{
    struct Color;
    class Page;

    class Font
    {
    public:
        /**
         * @brief Create a Glyph object for the specified character.
         */
        virtual Glyph CreateGlyph( wchar_t ch ) = 0;

        // TODO: Move print routines to a Page class?
        /**
         * @brief Resets information about the last printed glyph.
         */
        virtual void ResetLastPrintedGlyph() = 0;

        /**
         * @brief Prints a glyph on a page in a specified color at a specified position.
         *
         * @param page the page we will print on.
         * @param glyph glyph to be printed.
         * @param x abscissa of print position.
         * @param y print position ordinate.
         * @param color glyph color.
         * @return std::pair<double, double> coordinates of the point where the next glyph will be
         * printed.
         */
        virtual std::pair<double, double>
        PrintGlyph( Page& page, const Glyph& glyph, double x, double y, const Color& color ) = 0;

        virtual ~Font() = default;
    };
} // namespace Minibook

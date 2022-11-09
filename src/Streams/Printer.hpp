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

#include <Interfaces/Stream.hpp>
#include <Structures/Page.hpp>
#include <Structures/Params.hpp>

namespace Minibook
{
    class Font;
    class Line;

    /**
     * @brief Forms a page from lines of glyphs
     */
    class Printer final : public Stream<const Page*>
    {
    public:
        Printer( const Params& params, Font& font, Stream<Line>& source );

        /**
         * @return nullptr, if end of stream reached
         */
        virtual const Page* Fetch() override;

    private:
        Params m_params;
        Font& m_font;
        Page m_page;
        Stream<Line>& m_source;
    };
} // namespace Minibook

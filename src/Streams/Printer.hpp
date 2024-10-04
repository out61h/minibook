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

#include "Types.hpp"

#include <Structures/Page.hpp>
#include <Structures/Params.hpp>

namespace Minibook
{
    class Font;
    class Line;

    /**
     * @brief Forms a page from lines of glyphs.
     */
    class Printer final : public PageStream
    {
    public:
        Printer( LineStream& source, Font& font, const Params& params );

        /**
         * @return nullptr, if the end of the stream is reached.
         */
        virtual const Page* Fetch() override;

    private:
        LineStream& m_source;
        Font& m_font;
        const Params& m_params;
        Page m_page;
    };
} // namespace Minibook

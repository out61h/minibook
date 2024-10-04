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

#include <cstdint>

namespace Minibook
{
    /**
     * @brief Writes the content of the page to PNG file with given name.
     */
    class PngWriter final : public SizeStream
    {
    public:
        explicit PngWriter( PagePathStream& source );

        /**
         * @return 0, if the end of the stream has been reached, otherwise the size of the written
         * PNG file.
         */
        size_t Fetch() override;

    private:
        PagePathStream& m_source;
    };
} // namespace Minibook

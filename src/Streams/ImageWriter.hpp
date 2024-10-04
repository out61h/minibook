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
    class Page;
    class Params;

    /**
     * @brief Writes the content of the page to a image file with given name.
     *
     * Only PNG or JPEG image file formats are supported.
     */
    class ImageWriter final : public SizeStream
    {
    public:
        ImageWriter( PagePathStream& source, const Params& params );

        /**
         * @return 0, if the end of the stream has been reached, otherwise the size of the written
         * image file.
         */
        size_t Fetch() override;

    private:
        PagePathStream& m_source;
        const Params& m_params;
    };
} // namespace Minibook

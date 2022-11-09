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
#include <Structures/Params.hpp>

#include <memory>
#include <string>

namespace Minibook
{
    class Page;

    /**
     * @brief Writes the content of the page to a image file with given name
     */
    class ImageWriter final : public Stream<size_t>
    {
    public:
        using SourceStream = Stream<std::pair<const Page*, std::string>>;

        ImageWriter( SourceStream& source, const Params& params );

        /**
         * @return 0, if end of stream reached, otherwise file size of written JPEG
         */
        virtual size_t Fetch() override;

    private:
        SourceStream& m_source;
        Params m_params;
    };
} // namespace Minibook

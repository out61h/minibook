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

#include <memory>
#include <string>

namespace Minibook
{
    class Page;

    /**
     * @brief Writes the content of the page to a PNG file with given name
     */
    class PngWriter final : public Stream<size_t>
    {
    public:
        using SourceStream = Stream<std::pair<const Page*, std::string>>;

        explicit PngWriter( SourceStream& source );

        /**
         * @return 0, if end of stream reached, otherwise file size of written PNG
         */
        virtual size_t Fetch() override;

    private:
        SourceStream& m_source;
    };
} // namespace Minibook

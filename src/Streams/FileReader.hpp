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

#include <fstream>
#include <optional>

namespace Minibook
{
    /**
     * @brief Reads octet stream from file
     */
    class FileReader final : public Stream<std::optional<uint8_t>>
    {
    public:
        explicit FileReader( const std::string& filename );

        /**
         * @return no value, if end of stream reached
         */
        virtual std::optional<uint8_t> Fetch() override;

        double GetProgress() const;

    private:
        std::ifstream m_input;
        std::uintmax_t m_size;
        std::uintmax_t m_read;
    };
} // namespace Minibook

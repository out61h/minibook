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

#include <filesystem>
#include <fstream>
#include <optional>

namespace Minibook
{
    /**
     * @brief Produces a stream of octets from a file.
     */
    class FileReader final : public OctetStream
    {
    public:
        explicit FileReader( const std::filesystem::path& file );

        /**
         * @return no value, if the end of the stream is reached.
         */
        std::optional<uint8_t> Fetch() override;

        /**
         * @brief Returns the progress of reading a file as a normalized value.
         */
        double GetProgress() const;

    private:
        std::ifstream m_input;
        std::uintmax_t m_size;
        std::uintmax_t m_read;
    };
} // namespace Minibook

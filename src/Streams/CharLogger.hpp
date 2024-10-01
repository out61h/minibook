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
#include <string>

namespace Minibook
{
    /**
     * @brief Passes a stream of characters through itself unchanged and writes it to a file.
     */
    class CharLogger final : public CharStream
    {
    public:
        /**
         * @brief Construct a new CharLogger object.
         *
         * @param source Source stream of chars.
         * @param file Path to a file for logging.
         * @param enabled Enabling logging.
         */
        CharLogger( CharStream& source, const std::filesystem::path& file, bool enabled );

        /**
         * @return no value, if the end of the stream is reached.
         */
        std::optional<wchar_t> Fetch() override;

    private:
        CharStream& m_source;

        std::wofstream m_log;
    };
} // namespace Minibook

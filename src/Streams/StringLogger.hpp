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
#include <string>

namespace Minibook
{
    /**
     * @brief Passes a stream of words through itself unchanged and writes words to a file.
     */
    class StringLogger final : public WordStream
    {
    public:
        /**
         * @brief Construct a new StringLogger object.
         *
         * @param source Source stream of words.
         * @param file Path to a file for logging.
         * @param enabled If \true, enable logging.
         */
        StringLogger( WordStream& source, const std::filesystem::path& filename, bool enabled );

        /**
         * @return empty string, if the end of the stream is reached.
         */
        std::wstring Fetch() override;

    private:
        WordStream& m_source;

        std::wofstream m_log;
    };
} // namespace Minibook

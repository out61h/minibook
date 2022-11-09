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
#include <string>

namespace Minibook
{
    /**
     * @brief Passes a characters stream through itself unchanged and logs it to a file
     */
    class CharLogger final : public Stream<std::optional<wchar_t>>
    {
    public:
        CharLogger( Stream<std::optional<wchar_t>>& source,
                    std::string_view filename,
                    bool enabled );

        /**
         * @return no value, if end of stream reached
         */
        virtual std::optional<wchar_t> Fetch() override;

    private:
        Stream<std::optional<wchar_t>>& m_source;

        std::wofstream m_log;
    };
} // namespace Minibook

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

#include <string>
#include <optional>

namespace Minibook
{
    /**
     * @brief Breaks the input stream of characters into tokens
     *
     * A lexeme is a group of characters that does not contain a space.
     */
    class WordBreaker final : public Stream<std::wstring>
    {
    public:
        using CharStream = Stream<std::optional<wchar_t>>;

        explicit WordBreaker( CharStream& source );

        /**
         * @return empty string, if end of stream reached
         */
        virtual std::wstring Fetch() override;

    private:
        CharStream& m_source;
    };
} // namespace Minibook

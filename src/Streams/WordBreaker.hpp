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

namespace Minibook
{
    /**
     * @brief Splits a stream of characters into a stream of words.
     *
     * A word in this context is a group of characters that does not contain a space.
     */
    class WordBreaker final : public WordStream
    {
    public:
        explicit WordBreaker( CharStream& source );

        /**
         * @return empty string, if the end of the stream is reached.
         */
        std::wstring Fetch() override;

    private:
        CharStream& m_source;
    };
} // namespace Minibook

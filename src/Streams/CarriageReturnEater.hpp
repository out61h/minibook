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

#include <optional>

namespace Minibook
{
    /**
     * @brief Removes CR symbols from input stream.
     */
    class CarriageReturnEater final : public CharStream
    {
    public:
        explicit CarriageReturnEater( CharStream& source );

        /**
         * @return no value, if end of stream reached.
         */
        std::optional<wchar_t> Fetch() override;

    private:
        CharStream& m_source;
    };
} // namespace Minibook

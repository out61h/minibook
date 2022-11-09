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

#include <optional>

namespace Minibook
{
    /**
     * @brief Removes CR symbols from input stream
     */
    class CarriageReturnEater final : public Stream<std::optional<wchar_t>>
    {
    public:
        using CharStream = Stream<std::optional<wchar_t>>;

        explicit CarriageReturnEater( CharStream& source );

        /**
         * @return no value, if end of stream reached
         */
        virtual std::optional<wchar_t> Fetch() override;

    private:
        CharStream& m_source;
    };
} // namespace Minibook

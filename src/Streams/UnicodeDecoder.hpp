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
     * @brief Decodes wchar_t characters from a stream of UTF-8 octets
     */
    class UnicodeDecoder final : public Stream<std::optional<wchar_t>>
    {
    public:
        using OctetStream = Stream<std::optional<uint8_t>>;

        explicit UnicodeDecoder( OctetStream& source );

        /**
         * @return no value, if end of stream reached
         */
        virtual std::optional<wchar_t> Fetch() override;

    private:
        enum class State
        {
            ReadFirstOctet,
            ReadOneOctet,
            ReadTwoOctets,
            ReadThreeOctets,

            ExpectedBOM,
            ExpectedBB,
            ExpectedBF,

            Terminated,

            DetectedUTF8,

            Succeeded,
            Failed
        };

        OctetStream& m_source;
        State m_state;
    };
} // namespace Minibook

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
     * @brief Removes LF symbols that are not paragraph separators from input stream
     */
    class LineUnwrapper final : public Stream<std::optional<wchar_t>>
    {
    public:
        using CharStream = Stream<std::optional<wchar_t>>;

        explicit LineUnwrapper( CharStream& source );

        /**
         * @return no value, if end of stream reached
         */
        virtual std::optional<wchar_t> Fetch() override;

    private:
        CharStream& m_source;

        enum class State
        {
            EatingLineFeeds,
            EatingLeadingWhitespaces,
            StreamingChar,
            StreamingBufferedChar
        };

        State m_state;
        State m_nextState;
        wchar_t m_bufferedChar;
    };

} // namespace Minibook

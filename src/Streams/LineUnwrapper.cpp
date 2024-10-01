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
#include "LineUnwrapper.hpp"

#include <Constants/Chars.hpp>

#include <cstdio>

using namespace Minibook;

LineUnwrapper::LineUnwrapper( CharStream& source )
    : m_source( source )
{
}

// TODO: Eat extra spaces, add tabs at the beginning of a paragraph, and spaces after and before
// punctuation
// TODO: Leave the LF that comes after the . ... ! ?
// TODO: Use tabular FSM.
std::optional<wchar_t> LineUnwrapper::Fetch()
{
    if ( m_state == State::StreamBufferedChar )
    {
        m_state = m_nextState;
        return m_bufferedChar;
    }

    wchar_t result = 0;

    for ( ;; )
    {
        const auto ch = m_source.Fetch();
        if ( !ch )
            return {};

        result = *ch;

        if ( m_state == State::EatLineFeeds )
        {
            // TODO: Not only spaces, but also tabs
            if ( result == Chars::kSpace )
            {
                // After line breaks, there are spaces. Most likely it is a simulation of a
                // paragraph indent
                // TODO: whether it is necessary to "eat" whitespace?
                m_state = State::EatLeadingWhitespaces;
                // Add a LF character to the stream
                result = Chars::kLineFeed;
                break;
            }
            else if ( result == Chars::kLineFeed )
            {
                // After a LF there is a LF occured again, it is exactly a paragraph
                // TODO: whether it is necessary to "eat" LF?
                break;
            }
            else
            {
                // Most likely it's just wrapping the text in the sentence to a new line.
                // Add a space so the words don't concatenate
                m_bufferedChar = result;
                result = Chars::kSpace;
                m_state = State::StreamBufferedChar;
                break;
            }
        }
        else if ( m_state == State::EatLeadingWhitespaces )
        {
            if ( result == Chars::kLineFeed )
            {
                m_state = State::EatLineFeeds;
            }
            else if ( result != Chars::kSpace )
            {
                m_state = State::StreamChar;
                break;
            }
        }
        else if ( m_state == State::StreamChar )
        {
            if ( result == Chars::kLineFeed )
            {
                m_state = State::EatLineFeeds;
            }
            else
            {
                break;
            }
        }
    }

    return result;
}

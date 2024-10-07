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
#include "WordBreaker.hpp"

#include <Constants/Chars.hpp>

using namespace Minibook;

WordBreaker::WordBreaker( CharStream& source )
    : m_source( source )
{
}

std::wstring WordBreaker::Fetch()
{
    std::wstring result;

    bool skipLeadingWhitespaces = true;

    for ( ;; )
    {
        const auto ch = m_source.Fetch();
        if ( !ch )
            break;

        // remove leading spaces
        if ( skipLeadingWhitespaces && *ch == Chars::kSpace )
            continue;

        skipLeadingWhitespaces = false;

        // space == the beginning of a new word, give the current word
        if ( *ch == Chars::kSpace )
            break;

        result.push_back( *ch );

        // newline == the beginning of a new paragraph, give the current word
        if ( *ch == Chars::kLineFeed )
            break;

        // comma == the beginning of a new word, give the current word
        if ( *ch == Chars::kComma )
            break;

        // TODO: Add other delimeters
    }

    return result;
}

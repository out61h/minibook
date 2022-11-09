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
#include "CharLogger.hpp"

#include <locale>

using namespace Minibook;

CharLogger::CharLogger( Stream<std::optional<wchar_t>>& source,
                        std::string_view filename,
                        bool enabled )
    : m_source( source )
{
    if ( enabled )
    {
        m_log.open( filename.data() );

        std::locale utf8locale(
            std::locale(),
            new std::codecvt_byname<wchar_t, char, std::mbstate_t>( "en_US.UTF-8" ) );
        m_log.imbue( utf8locale );
    }
}

std::optional<wchar_t> CharLogger::Fetch()
{
    const auto ch = m_source.Fetch();

    if ( m_log.is_open() && ch )
        m_log << *ch;

    return ch;
}

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
#include "CarriageReturnEater.hpp"

#include "Constants/Chars.hpp"

using namespace Minibook;

CarriageReturnEater::CarriageReturnEater( CharStream& source )
    : m_source( source )
{
}

std::optional<wchar_t> CarriageReturnEater::Fetch()
{
    wchar_t result = 0;

    for ( ;; )
    {
        const auto character = m_source.Fetch();
        if ( !character )
            return {};

        result = *character;

        if ( result != Chars::kCarriageReturn )
            break;
    }

    return result;
}

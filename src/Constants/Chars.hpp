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

#include <cwchar>

namespace Minibook
{
    namespace Chars
    {
        constexpr wchar_t kCarriageReturn = L'\r';
        constexpr wchar_t kComma = L',';
        constexpr wchar_t kLineFeed = L'\n';
        constexpr wchar_t kSoftHyphen = L'\xad';
        constexpr wchar_t kSpace = L' ';
        constexpr wchar_t kTabulation = L'\t';
        constexpr wchar_t kPilcrowSign = L'\xB6';
        constexpr wchar_t kWhiteSquare = L'\x25A1';
    } // namespace Chars
} // namespace Minibook

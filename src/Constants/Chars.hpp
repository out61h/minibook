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

#include <cwchar>

namespace Minibook
{
    namespace Chars
    {
        const wchar_t kCarriageReturn = L'\r';
        const wchar_t kComma = L',';
        const wchar_t kLineFeed = L'\n';
        const wchar_t kSoftHyphen = L'\xad';
        const wchar_t kSpace = L' ';
        const wchar_t kTabulation = L'\t';
    } // namespace Chars

} // namespace Minibook

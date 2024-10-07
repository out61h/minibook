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

namespace Minibook
{
    struct Size
    {
        Size() = default;

        Size( double width, double height )
            : Width( width )
            , Height( height )
        {
        }

        double Width = 0.;
        double Height = 0.;
    };
} // namespace Minibook

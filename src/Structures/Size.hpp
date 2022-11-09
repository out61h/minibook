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

namespace Minibook
{
    struct Size
    {
        Size()
            : Width( 0. )
            , Height( 0. )
        {
        }

        Size( double width, double height )
            : Width( width )
            , Height( height )
        {
        }

        double Width;
        double Height;
    };
} // namespace Minibook

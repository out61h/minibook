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
    struct Margin
    {
        Margin()
            : Top( 0. )
            , Right( 0. )
            , Bottom( 0. )
            , Left( 0. )
        {
        }

        Margin( double top, double right, double bottom, double left )
            : Top( top )
            , Right( right )
            , Bottom( bottom )
            , Left( left )
        {
        }

        double Top;
        double Right;
        double Bottom;
        double Left;
    };
} // namespace Minibook

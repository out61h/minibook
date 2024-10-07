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
    struct Margin
    {
        Margin() = default;

        Margin( double top, double right, double bottom, double left )
            : Top( top )
            , Right( right )
            , Bottom( bottom )
            , Left( left )
        {
        }

        double Top = 0.;
        double Right = 0.;
        double Bottom = 0.;
        double Left = 0.;
    };
} // namespace Minibook

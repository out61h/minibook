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

#include <stdexcept>

namespace Minibook
{
    namespace Exceptions
    {
        class FunctionFailed final : public std::runtime_error
        {
        public:
            explicit FunctionFailed( std::string_view functionName )
                : std::runtime_error( std::string( functionName ) + "() failed" )
            {
            }
        };
    } // namespace Exceptions
    
} // namespace Minibook

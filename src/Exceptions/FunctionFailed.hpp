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

#pragma once

#include <stdexcept>

namespace Minibook
{
    namespace Exceptions
    {
        class BadUnicodeData final : public std::runtime_error
        {
        public:
            BadUnicodeData()
                : std::runtime_error( "Bad unicode data" )
            {
            }
        };
    } // namespace Exceptions

} // namespace Minibook

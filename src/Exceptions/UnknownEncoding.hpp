#pragma once

#include <stdexcept>

namespace Minibook
{
    namespace Exceptions
    {
        class UnknownEncoding final : public std::runtime_error
        {
        public:
            UnknownEncoding()
                : std::runtime_error( "Unknown encoding" )
            {
            }
        };
    } // namespace Exceptions

} // namespace Minibook

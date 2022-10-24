#pragma once

#include <stdexcept>

namespace Minibook
{
    namespace Exceptions
    {
        class FileNotOpened final : public std::runtime_error
        {
        public:
            explicit FileNotOpened( std::string_view filePath )
                : std::runtime_error( std::string( "File not found: " ) + std::string( filePath ) )
            {
            }
        };
    } // namespace Exceptions
    
} // namespace Minibook

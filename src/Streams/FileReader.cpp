#include "FileReader.hpp"

#include <Exceptions/FileNotOpened.hpp>

#include <filesystem>

using namespace Minibook;

FileReader::FileReader( const std::string& filename )
    : m_input( filename.c_str(), std::ios::in | std::ios::binary )
    , m_read( 0 )
{
    if ( !m_input.is_open() )
        throw Exceptions::FileNotOpened( filename );

    m_size = std::filesystem::file_size( filename );
}

std::optional<uint8_t> FileReader::Fetch()
{
    if ( m_input.eof() )
        return {};

    char ch = 0;
    m_input.read( &ch, 1 );
    m_read++;
    return static_cast<uint8_t>( ch );
}

double FileReader::GetProgress() const
{
    return (double)m_read / (double)m_size;
}

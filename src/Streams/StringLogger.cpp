#include "StringLogger.hpp"

#include <locale>

using namespace Minibook;

StringLogger::StringLogger( Stream<std::wstring>& source, std::string_view filename, bool enabled )
    : m_source( source )
{
    if ( enabled )
    {
        m_log.open( filename.data() );

        std::locale utf8locale(
            std::locale(),
            new std::codecvt_byname<wchar_t, char, std::mbstate_t>( "en_US.UTF-8" ) );
        m_log.imbue( utf8locale );
    }
}

std::wstring StringLogger::Fetch()
{
    std::wstring string = m_source.Fetch();

    if ( m_log.is_open() )
        m_log << string << std::endl;

    return string;
}

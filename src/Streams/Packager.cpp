#include "Packager.hpp"

#include <filesystem>
#include <sstream>

using namespace Minibook;

Packager::Packager( SourceStream& source, std::string_view folder, int pagesPerChapter )
    : m_source( source )
    , m_outputFolder( folder )
    , m_pagesPerChapter( pagesPerChapter )
    , m_pagesCounter( 0 )
    , m_pagesChapter( 0 )
{
    std::filesystem::create_directory( m_outputFolder );
}

std::pair<const Page*, std::string> Packager::Fetch()
{
    const Page* page = m_source.Fetch();

    if ( !page )
        return {};

    if ( !( m_pagesCounter % m_pagesPerChapter ) )
    {
        m_pagesChapter = m_pagesCounter;

        std::ostringstream directoryName;
        directoryName << m_outputFolder;
        directoryName << '/';
        directoryName << std::setfill( '0' ) << std::setw( 4 ) << m_pagesChapter;

        m_chapterFolder = directoryName.str();

        std::filesystem::create_directory( m_chapterFolder );
    }

    std::ostringstream fileName;
    fileName << m_chapterFolder;
    fileName << '/';
    fileName << std::setfill( '0' ) << std::setw( 4 ) << m_pagesCounter++;

    return { page, fileName.str() };
}

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
#include "Packager.hpp"

#include <sstream>

using namespace Minibook;

Packager::Packager( PageStream& source,
                    const std::filesystem::path& outputDir,
                    int pagesPerChapter )
    : m_source( source )
    , m_outputDir( outputDir )
    , m_pagesPerChapter( pagesPerChapter )
    , m_chapterDir( outputDir )
{
    std::filesystem::create_directory( m_outputDir );
}

std::pair<const Page*, std::filesystem::path> Packager::Fetch()
{
    const Page* page = m_source.Fetch();

    if ( !page )
        return {};

    if ( m_pagesPerChapter > 0 && !( m_pageCounter % m_pagesPerChapter ) )
    {
        std::ostringstream chapterSubdir;
        chapterSubdir << std::setfill( '0' ) << std::setw( 4 ) << m_pageCounter;

        m_chapterDir = m_outputDir / chapterSubdir.str();

        std::filesystem::create_directory( m_chapterDir );
    }

    std::ostringstream pageFilename;
    pageFilename << std::setfill( '0' ) << std::setw( 4 ) << m_pageCounter++;

    return { page, m_chapterDir / pageFilename.str() };
}

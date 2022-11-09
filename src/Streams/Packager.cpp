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

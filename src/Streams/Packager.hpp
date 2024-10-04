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
#pragma once

#include "Types.hpp"

#include <filesystem>
#include <string>
#include <utility>

namespace Minibook
{
    class Page;

    /**
     * @brief Generates file names for saving page images, splitting them into subdirectories.
     */
    class Packager final : public PagePathStream
    {
    public:
        /**
         * @brief Construct a new Packager object.
         *
         * @param source Source of pages.
         * @param outputDir Path to output directory.
         * @param pagesPerChapter Pages per chapters subdirectory.
         *
         * If \pagesPerChapter is set to 0, no subdirectories are created.
         */
        Packager( PageStream& source, const std::filesystem::path& outputDir, int pagesPerChapter );

        /**
         * Return a pair of a \Page and its save location (path with file name without
         * extension).
         *
         * @return nullptr with empty path, if the end of the stream is reached.
         */
        std::pair<const Page*, std::filesystem::path> Fetch() override;

    private:
        PageStream& m_source;

        const std::filesystem::path m_outputDir;
        const int m_pagesPerChapter;

        std::filesystem::path m_chapterDir;
        int m_pageCounter = 0;
    };
} // namespace Minibook

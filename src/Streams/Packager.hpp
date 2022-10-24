#pragma once

#include <Interfaces/Stream.hpp>

#include <string>
#include <utility>

namespace Minibook
{
    class Page;

    /**
     * @brief Generates filenames for saving images using splitting them into subfolders
     */
    class Packager final : public Stream<std::pair<const Page*, std::string>>
    {
    public:
        using SourceStream = Stream<const Page*>;

        Packager( SourceStream& source, std::string_view folder, int pagesPerChapter );

        /**
         * @return nullptr with empty string, if end of stream reached
         */
        virtual std::pair<const Page*, std::string> Fetch() override;

    private:
        SourceStream& m_source;
        std::string m_outputFolder;
        int m_pagesPerChapter;
        int m_pagesCounter;
        int m_pagesChapter;
        std::string m_chapterFolder;
    };
} // namespace Minibook

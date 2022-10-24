#pragma once

#include <Interfaces/Stream.hpp>

#include <memory>
#include <string>

namespace Minibook
{
    class Page;

    /**
     * @brief Writes the content of the page to a PNG file with given name
     */
    class PngWriter final : public Stream<size_t>
    {
    public:
        using SourceStream = Stream<std::pair<const Page*, std::string>>;

        explicit PngWriter( SourceStream& source );

        /**
         * @return 0, if end of stream reached, otherwise file size of written PNG
         */
        virtual size_t Fetch() override;

    private:
        SourceStream& m_source;
    };
} // namespace Minibook

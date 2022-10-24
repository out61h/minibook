#pragma once

#include <Interfaces/Stream.hpp>
#include <Structures/Params.hpp>

#include <memory>
#include <string>

namespace Minibook
{
    class Page;

    /**
     * @brief Writes the content of the page to a image file with given name
     */
    class ImageWriter final : public Stream<size_t>
    {
    public:
        using SourceStream = Stream<std::pair<const Page*, std::string>>;

        ImageWriter( SourceStream& source, const Params& params );

        /**
         * @return 0, if end of stream reached, otherwise file size of written JPEG
         */
        virtual size_t Fetch() override;

    private:
        SourceStream& m_source;
        Params m_params;
    };
} // namespace Minibook

#include "ImageWriter.hpp"

#include <Structures/Page.hpp>
#include <Structures/Params.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <filesystem>

using namespace Minibook;

namespace
{
    bool IsJpegFormat( const Params& params )
    {
        return params.Typesetter.Format == "jpg" || params.Typesetter.Format == "jpeg";
    }
} // namespace

ImageWriter::ImageWriter( SourceStream& source, const Params& params )
    : m_source( source )
    , m_params( params )
{
}

size_t ImageWriter::Fetch()
{
    const auto& pair = m_source.Fetch();
    if ( !pair.first )
        return 0;

    const Page* page = pair.first;

    const std::string filename = pair.second + "." + m_params.Typesetter.Format;

    if ( IsJpegFormat( m_params ) )
    {
        stbi_write_jpg( filename.data(),
                        page->GetWidth(),
                        page->GetHeight(),
                        3,
                        page->GetBuffer(),
                        m_params.Typesetter.Jpg.Quality );
    }
    else
    {
        const int level = stbi_write_png_compression_level;
        stbi_write_png_compression_level = m_params.Typesetter.Png.Compression;

        stbi_write_png( filename.data(),
                        page->GetWidth(),
                        page->GetHeight(),
                        3,
                        page->GetBuffer(),
                        3 * page->GetWidth() );

        stbi_write_png_compression_level = level;
    }

    return std::filesystem::file_size( filename );
}

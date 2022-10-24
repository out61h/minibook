#include "PngWriter.hpp"

#include <Exceptions/FileNotOpened.hpp>
#include <Exceptions/FunctionFailed.hpp>
#include <Structures/Page.hpp>

#include <png.h>

#include <cassert>
#include <cstdio>
#include <filesystem>
#include <vector>

using namespace Minibook;

namespace
{
    constexpr int kBitDepth = 4;
    constexpr int kPixelsPerByte = 2;
} // namespace

struct Png
{
    Png()
        : Struct( png_create_write_struct( PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr ) )
        , Info( png_create_info_struct( Struct ) )
    {
        if ( !Struct )
            throw Exceptions::FunctionFailed( "png_create_write_struct" );

        if ( !Info )
            throw Exceptions::FunctionFailed( "png_create_info_struct" );
    }

    ~Png()
    {
        png_destroy_write_struct( &Struct, &Info );
    }

    png_structp Struct;
    png_infop Info;
};

class Impl final
{
public:
    Impl( size_t width, size_t height )
        : m_width( width )
        , m_height( height )
        , m_rows( height, nullptr )
    {
        assert( width % kPixelsPerByte == 0 );

        for ( size_t row = 0; row < height; ++row )
            m_rows[row] = new png_byte[( width + 1 ) / kPixelsPerByte];
    }

    ~Impl()
    {
        for ( auto& row : m_rows )
            delete[] row;
    }

    void SetPixel( size_t col, size_t row, uint8_t pix )
    {
        assert( col < width && row < height );

        png_byte byte = m_rows[row][col / kPixelsPerByte];

        byte = ( col % kPixelsPerByte ) ? ( byte & 0xf0 ) + ( 0x0f & pix )
                                        : ( byte & 0x0f ) + ( ( 0x0f & pix ) << kBitDepth );

        m_rows[row][col / kPixelsPerByte] = byte;
    }

    void SaveToFile( std::string_view filename )
    {
        std::unique_ptr<FILE, decltype( &fclose )> fp( fopen( filename.data(), "wb" ), &fclose );
        if ( !fp )
            throw Exceptions::FileNotOpened( filename );

        Png png;

        if ( setjmp( png_jmpbuf( png.Struct ) ) )
            throw Exceptions::FunctionFailed( "png_init_io" );

        png_init_io( png.Struct, fp.get() );

        if ( setjmp( png_jmpbuf( png.Struct ) ) )
            throw Exceptions::FunctionFailed( "png_set_IHDR" );

        png_set_IHDR( png.Struct,
                      png.Info,
                      m_width,
                      m_height,
                      kBitDepth,
                      PNG_COLOR_TYPE_GRAY,
                      PNG_INTERLACE_NONE,
                      PNG_COMPRESSION_TYPE_BASE,
                      PNG_FILTER_TYPE_BASE );

        if ( setjmp( png_jmpbuf( png.Struct ) ) )
            throw Exceptions::FunctionFailed( "png_write_info" );

        png_write_info( png.Struct, png.Info );

        if ( setjmp( png_jmpbuf( png.Struct ) ) )
            throw Exceptions::FunctionFailed( "png_write_image" );

        png_write_image( png.Struct, m_rows.data() );

        if ( setjmp( png_jmpbuf( png.Struct ) ) )
            throw Exceptions::FunctionFailed( "png_write_end" );

        png_write_end( png.Struct, nullptr );
    }

private:
    std::size_t m_width;
    std::size_t m_height;
    std::vector<png_bytep> m_rows;
};

PngWriter::PngWriter( SourceStream& source )
    : m_source( source )
{
}

size_t PngWriter::Fetch()
{
    const auto& pair = m_source.Fetch();
    if ( !pair.first )
        return 0;

    const Page* page = pair.first;

    Impl impl( page->GetWidth(), page->GetHeight() );

    for ( int y = 0; y < page->GetHeight(); ++y )
    {
        for ( int x = 0; x < page->GetWidth(); ++x )
        {
            impl.SetPixel( x, y, ( *page )( x, y ) >> kBitDepth );
        }
    }

    const std::string filename = pair.second + ".png";
    impl.SaveToFile( filename );

    return std::filesystem::file_size( filename );
}

#include <Exceptions/BadUnicodeData.hpp>
#include <Exceptions/FileNotOpened.hpp>
#include <Exceptions/UnknownEncoding.hpp>
#include <Implementations/TrueTypeFont.hpp>
#include <Streams/CarriageReturnEater.hpp>
#include <Streams/CharLogger.hpp>
#include <Streams/FileReader.hpp>
#include <Streams/LineUnwrapper.hpp>
#include <Streams/Packager.hpp>
#include <Streams/PngWriter.hpp>
#include <Streams/Printer.hpp>
#include <Streams/StringLogger.hpp>
#include <Streams/Typesetter.hpp>
#include <Streams/UnicodeDecoder.hpp>
#include <Streams/WordHyphenator.hpp>
#include <Streams/Wordbreaker.hpp>

#include <filesystem>
#include <iostream>

using namespace Minibook;

int main( int argc, char* argv[] )
{
    try
    {
        std::string inputFileName;
        std::string configFileName;
        std::string outputFolder;
        bool needHelp = false;

        for ( int argi = 1; argi < argc; ++argi )
        {
            const std::string_view arg = argv[argi];

            if ( arg.starts_with( "--config=" ) )
            {
                configFileName = arg.substr( strlen( "--config=" ) );
            }
            else if ( arg.starts_with( "--help" ) )
            {
                needHelp = true;
                break;
            }
            else if ( arg.starts_with( "--output=" ) )
            {
                outputFolder = arg.substr( strlen( "--output=" ) );
            }
            else if ( arg.starts_with( "--" ) )
            {
                // do nothing
            }
            else
            {
                inputFileName = arg;
                break;
            }
        }

        if ( needHelp )
        {
            std::cerr << "Minibook - text to image converter." << std::endl;
            std::cerr << std::endl;
            std::cerr << "Usage:" << std::endl;
            std::cerr << "  Minibook [--config=<file>] [--output=<folder>] <textfile>";
            std::cerr << "  # Rasterizes input UTF8 encoded text file to PNG images" << std::endl;
            std::cerr << "  Minibook --config=<file>                                 ";
            std::cerr << "  # Exports default configuration to JSON file" << std::endl;
            std::cerr << "  Minibook --help                                          ";
            std::cerr << "  # Shows this screen" << std::endl;
            std::cerr << std::endl;
            std::cerr << "Options:" << std::endl;
            std::cerr << "--help             Shows this screen." << std::endl;
            std::cerr << "--config=<file>    Specifies JSON configuration file name." << std::endl;
            std::cerr << "--output=<folder>  Specifies output folder name." << std::endl;
            std::cerr << std::endl;

            return EXIT_SUCCESS;
        }

        if ( inputFileName.empty() && !configFileName.empty() )
        {
            // Export config and exit
            Params params;
            params.Save( configFileName );

            return EXIT_SUCCESS;
        }

        if ( inputFileName.empty() )
        {
            std::cerr << "Minibook --help" << std::endl;

            return EXIT_FAILURE;
        }

        if ( outputFolder.empty() )
        {
            std::filesystem::path path( inputFileName );
            outputFolder = path.stem().string();
        }

        Params params;

        if ( !configFileName.empty() )
            params.Load( configFileName );

        {
            using CharStream = Stream<std::optional<wchar_t>>;

            TrueTypeFont font( params.Font.Name, params.Font.Size, params.Font.Hinting );

            // read octets from text file with UTF8 encoding, decode wide chars and remove CR's
            FileReader reader( inputFileName );
            UnicodeDecoder decoder( reader );
            CarriageReturnEater eolConverter( decoder );

            // unwrap preformatted lines, break on words and insert soft hyphenation symbols
            LineUnwrapper unwrapper( eolConverter );
            CharLogger textLogger( params.Typesetter.Preprocessing
                                       ? static_cast<CharStream&>( unwrapper )
                                       : static_cast<CharStream&>( eolConverter ),
                                   "text.log",
                                   params.Typesetter.Logging );
            WordBreaker wordBreaker( textLogger );
            StringLogger wordBreakerLogger(
                wordBreaker, "wordbreaker.log", params.Typesetter.Logging );
            WordHyphenator hyphenator( wordBreakerLogger );
            StringLogger hyphenatorLogger(
                hyphenator, "hyphenator.log", params.Typesetter.Logging );

            // print text line-by-line
            Typesetter linebreaker( hyphenatorLogger, font, params );
            Printer printer( params, font, linebreaker );

            // save rastered text to PNG files
            Packager packager( printer, outputFolder, params.Chapter.Pages );
            PngWriter writer( packager );

            // main loop
            size_t fileSize = 0;
            size_t totalFileSize = 0;

            for ( int page = 1; ( fileSize = writer.Fetch() ) > 0; ++page )
            {
                std::cerr << "\r";
                std::cerr << "Page: " << std::setw( 4 ) << page << " ";
                std::cerr << "(" << std::fixed << std::setprecision( 0 )
                          << reader.GetProgress() * 100.0 << "%)";

                totalFileSize += fileSize;
            }

            std::cerr << std::endl;
            std::cerr << "Total file size: " << totalFileSize / 1024 << " KiB" << std::endl;
        }
    }
    catch ( const std::exception& ex )
    {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
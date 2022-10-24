#pragma once

#include <Interfaces/Stream.hpp>
#include <Structures/Page.hpp>
#include <Structures/Params.hpp>

namespace Minibook
{
    class Font;
    class Line;

    /**
     * @brief Forms a page from lines of glyphs
     */
    class Printer final : public Stream<const Page*>
    {
    public:
        Printer( const Params& params, Font& font, Stream<Line>& source );

        /**
         * @return nullptr, if end of stream reached
         */
        virtual const Page* Fetch() override;

    private:
        Params m_params;
        Font& m_font;
        Page m_page;
        Stream<Line>& m_source;
    };
} // namespace Minibook

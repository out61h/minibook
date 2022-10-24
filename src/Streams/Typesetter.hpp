#pragma once

#include <Interfaces/Stream.hpp>
#include <Structures/Line.hpp>

#include <cassert>
#include <string>

namespace Minibook
{
    class Font;
    class Params;

    /**
     * @brief Generates lines of glyphs of a given width from a stream of syllables
     */
    class Typesetter final : public Stream<Line>
    {
    public:
        Typesetter( Stream<std::wstring>& source, Font& font, const Params& params );

        /**
         * @return empty glyph string if end of stream reached
         */
        virtual Line Fetch() override;

    private:
        Stream<std::wstring>& m_source;

        Font& m_font;

        const bool m_justification;
        const double m_spaceWith;
        const double m_lineWidth;
        const double m_lineSpacing;
        const double m_paragraphSpacing;
        const double m_paragraphIndent;

        std::wstring m_text;
        bool m_startNewParagraph;
    };
} // namespace Minibook

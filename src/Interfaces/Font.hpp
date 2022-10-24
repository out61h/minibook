#pragma once

#include <Structures/Color.hpp>
#include <Structures/Glyph.hpp>

#include <utility>

namespace Minibook
{
    class Page;

    class Font
    {
    public:
        virtual Glyph CreateGlyph( wchar_t ch ) = 0;

        virtual void BeginDraw() = 0;

        virtual std::pair<double, double>
        DrawGlyph( Page& page, const Glyph& glyph, double x, double y, Color color ) = 0;

        virtual ~Font() = default;
    };
} // namespace Minibook

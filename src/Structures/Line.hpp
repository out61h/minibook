#pragma once

#include <Structures/Glyph.hpp>

#include <string>
#include <vector>

namespace Minibook
{
    class Line final
    {
    public:
        void Append( const Glyph& glyph );
        void Append( const Line& glyphs );
        void RemoveLast();

        const Glyph& operator[]( size_t index ) const;
        const Glyph GetLast() const;
        size_t GetSize() const;
        bool IsEmpty() const;

        bool IsEndsWith( wchar_t ch ) const;

        void Justify( double lineWidth );

        double GetWidth() const;
        double GetHeight() const;

        void SetHeight( double height );

    private:
        std::vector<Glyph> m_glyphs;
        double m_width{ 0. };
        double m_height{ 0. };
    };
} // namespace Minibook

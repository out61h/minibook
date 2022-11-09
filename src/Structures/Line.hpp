/*
 * Copyright (C) 2016-2022 Konstantin Polevik
 * All rights reserved
 *
 * This file is part of the Minibook. Redistribution and use in source and
 * binary forms, with or without modification, are permitted exclusively
 * under the terms of the MIT license. You should have received a copy of the
 * license with this file. If not, please visit:
 * https://github.com/out61h/minibook/blob/main/LICENSE
 */
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

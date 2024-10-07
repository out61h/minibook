/*
 * Copyright (C) 2016-2024 Konstantin Polevik
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
    /**
     * @brief Line of glyphs.
     */
    class Line final
    {
    public:
        /**
         * @brief Adds the specified glyph to the end. The line width increases.
         */
        void AppendGlyph( const Glyph& glyph );

        /**
         * @brief Adds the specified line of glyphs to the end. The line width increases.
         */
        void AppendLine( const Line& glyphs );

        /**
         * @brief Removes a glyph from the end. The line width decreases.
         */
        void RemoveLastGlyph();

        /**
         * @brief Checking if a line is empty.
         */
        bool IsEmpty() const;

        /**
         * @brief Returns the number of glyphs in a line.
         */
        size_t GetGlyphCount() const;

        /**
         * @brief Returns the glyph at the specified ordinal position.
         */
        const Glyph& operator[]( size_t index ) const;

        /**
         * @brief Returns the glyph located at the end.
         */
        const Glyph& GetLastGlyph() const;

        /**
         * @brief Checks if a string ends with the specified glyph.
         */
        bool IsEndsWithGlyph( wchar_t ch ) const;

        /**
         * @brief Returns the total width of glyphs in the line.
         */
        double GetWidth() const;

        /**
         * @brief Returns the height of the line.
         */
        double GetHeight() const;

        /**
         * @brief Sets the height of the line.
         */
        void SetHeight( double height );

        /**
         * @brief Sets the width of whitespace glyphs to make the line width equal to the specified
         * one.
         *
         * If the total width of the glyphs exceeds the specified width, does nothing.
         */
        void JustifyGlyphs( double lineWidth );

    private:
        std::vector<Glyph> m_glyphs;
        double m_width = 0.;
        double m_height = 0.;
    };
} // namespace Minibook

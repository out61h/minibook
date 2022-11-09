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

#include <string>

#include "Color.hpp"
#include "Margin.hpp"
#include "Size.hpp"

namespace Minibook
{
    class Params final
    {
    public:
        void Load( std::string_view filename );
        void Save( std::string_view filename );

        struct Page
        {
            Color Color{ 1., 1., 1. };
            double Gamma{ 0.8 };
            Margin Margin{ 28., 2., 18., 2. };
            Size Size{ 128., 160. };
        } Page;

        struct Line
        {
            bool Justification{ true };
            double Spacing{ 1. };
        } Line;

        struct Paragraph
        {
            double Indent{ 3. };
            double Spacing{ .2 };
        } Paragraph;

        struct Font
        {
            Color Color{ 0., 0., 0. };
            bool Hinting{ true };
            std::string Name{ "DroidSans.ttf" };
            double Size{ 10. };

        } Font;

        struct Chapter
        {
            int Pages{ 50 };
        } Chapter;

        struct Typesetter
        {
            bool Preprocessing{ true };
            bool Logging{ false };
            std::string Format{ "png" };

            struct Jpg
            {
                int Quality{ 20 };
            } Jpg;

            struct Png
            {
                int Compression{ 9 };
            } Png;
        } Typesetter;
    };
} // namespace Minibook

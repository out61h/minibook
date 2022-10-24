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
            bool Logging = false;
        } Typesetter;
    };
} // namespace Minibook

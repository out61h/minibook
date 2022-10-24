#include "Params.hpp"

#include <nlohmann/json.hpp>

#include <fstream>

namespace agg
{
    void to_json( nlohmann::json& j, const rgba& o )
    {
        j = nlohmann::json{ { "red", o.r }, { "green", o.g }, { "blue", o.b }, { "alpha", o.a } };
    }

    void from_json( const nlohmann::json& j, rgba& o )
    {
        j.at( "red" ).get_to( o.r );
        j.at( "green" ).get_to( o.g );
        j.at( "blue" ).get_to( o.b );
        j.at( "alpha" ).get_to( o.a );
    }
} // namespace agg

namespace Minibook
{
    void to_json( nlohmann::json& j, const Size& s )
    {
        j = nlohmann::json{ { "width", s.Width }, { "height", s.Height } };
    }

    void from_json( const nlohmann::json& j, Size& s )
    {
        j.at( "width" ).get_to( s.Width );
        j.at( "height" ).get_to( s.Height );
    }

    void to_json( nlohmann::json& j, const Margin& m )
    {
        j = nlohmann::json{
            { "left", m.Left }, { "top", m.Top }, { "right", m.Right }, { "bottom", m.Bottom } };
    }

    void from_json( const nlohmann::json& j, Margin& m )
    {
        j.at( "left" ).get_to( m.Left );
        j.at( "top" ).get_to( m.Top );
        j.at( "right" ).get_to( m.Right );
        j.at( "bottom" ).get_to( m.Bottom );
    }
} // namespace Minibook

using namespace Minibook;

void Params::Load( std::string_view filename )
{
    std::ifstream stream( filename.data() );
    nlohmann::json json;
    stream >> json;

    {
        const auto& font = json.at( "font" );

        Font.Color = font.at( "color" ).get<Color>();
        Font.Hinting = font.at( "hinting" ).get<bool>();
        Font.Name = font.at( "name" ).get<std::string>();
        Font.Size = font.at( "size" ).get<double>();
    }

    {
        const auto& page = json.at( "page" );

        Page.Color = page.at( "color" ).get<Color>();
        Page.Gamma = page.at( "gamma" ).get<double>();
        Page.Margin = page.at( "margin" ).get<Margin>();
        Page.Size = page.at( "size" ).get<Size>();
    }

    {
        const auto& line = json.at( "line" );

        Line.Justification = line.at( "justification" ).get<bool>();
        Line.Spacing = line.at( "spacing" ).get<double>();
    }

    {
        const auto& chapter = json.at( "chapter" );

        Chapter.Pages = chapter.at( "pages" ).get<int>();
    }

    {
        const auto& typesetter = json.at( "typesetter" );

        Typesetter.Logging = typesetter.at( "logging" ).get<bool>();
        Typesetter.Preprocessing = typesetter.at( "preprocessing" ).get<bool>();
    }

    {
        const auto& paragraph = json.at( "paragraph" );

        Paragraph.Indent = paragraph.at( "indent" ).get<double>();
        Paragraph.Spacing = paragraph.at( "spacing" ).get<double>();
    }

    Page.Margin.Top = std::clamp( Page.Margin.Top, 0., Page.Size.Height );
    Page.Margin.Bottom = std::clamp( Page.Margin.Bottom, 0., Page.Size.Height - Page.Margin.Top );
    Page.Margin.Left = std::clamp( Page.Margin.Left, 0., Page.Size.Width );
    Page.Margin.Right = std::clamp( Page.Margin.Right, 0., Page.Size.Width - Page.Margin.Left );
}

void Params::Save( std::string_view filename )
{
    // clang-format off
    const nlohmann::json json{
        { "font", {
            { "color", Font.Color },
            { "hinting", Font.Hinting },
            { "name", Font.Name },
            { "size", Font.Size }
        }},
        { "line", {
            { "justification", Line.Justification },
            { "spacing", Line.Spacing }
        }},
        { "page", {
            { "color", Page.Color },
            { "gamma", Page.Gamma },
            { "margin", Page.Margin },
            { "size", Page.Size }
        }},
        { "paragraph", {
            { "indent", Paragraph.Indent },
            { "spacing", Paragraph.Spacing }
        }},
        { "chapter", {
            { "pages", Chapter.Pages }
        }},
        { "typesetter", {
            { "logging", Typesetter.Logging },
            { "preprocessing", Typesetter.Preprocessing },
        }}
    };
    // clang-format on

    std::ofstream stream( filename.data() );
    stream << std::setw( 4 ) << json << std::endl;
}

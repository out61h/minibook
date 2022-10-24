#include "WordBreaker.hpp"

#include <Constants/Chars.hpp>

using namespace Minibook;

WordBreaker::WordBreaker( CharStream& source )
    : m_source( source )
{
}

std::wstring WordBreaker::Fetch()
{
    std::wstring result;

    bool skipLeadingWhitespaces = true;

    for ( ;; )
    {
        const auto ch = m_source.Fetch();
        if ( !ch )
            break;

        // remove leading spaces
        if ( skipLeadingWhitespaces && *ch == Chars::kSpace )
            continue;

        skipLeadingWhitespaces = false;

        result.push_back( *ch );

        // newline - the beginning of a new paragraph, give the current word
        if ( *ch == Chars::kLineFeed )
            break;

        // comma - the beginning of a new word, give the current word
        if ( *ch == Chars::kComma )
            break;

        // space - the beginning of a new word, give the current word
        if ( *ch == Chars::kSpace )
            break;
    }

    return result;
}

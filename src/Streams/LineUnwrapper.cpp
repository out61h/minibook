#include "LineUnwrapper.hpp"

#include <Constants/Chars.hpp>

#include <cstdio>

using namespace Minibook;

LineUnwrapper::LineUnwrapper( CharStream& source )
    : m_source( source )
    , m_state( State::EatingLeadingWhitespaces )
    , m_nextState( State::StreamingChar )
    , m_bufferedChar( 0 )
{
}

// TODO: Eat extra spaces, add tabs at the beginning of a paragraph, spaces after and before
// punctuation
// TODO: Leave the LF that comes after the . ... ! ?
std::optional<wchar_t> LineUnwrapper::Fetch()
{
    if ( m_state == State::StreamingBufferedChar )
    {
        m_state = m_nextState;
        return m_bufferedChar;
    }

    wchar_t result = 0;

    for ( ;; )
    {
        const auto ch = m_source.Fetch();
        if ( !ch )
            return {};

        result = *ch;

        if ( m_state == State::EatingLineFeeds )
        {
            // TODO: Not only spaces, but also tabs
            if ( result == Chars::kSpace )
            {
                // After the line breaks, there are spaces. Most likely this is a simulation of a
                // paragraph indent
                // TODO: whether it is necessary to "eat" whitespace?
                m_state = State::EatingLeadingWhitespaces;
                // Add a LF character to the stream
                result = Chars::kLineFeed;
                break;
            }
            else if ( result == Chars::kLineFeed )
            {
                // After a LF there is a LF occured again, this is exactly a paragraph
                // TODO: whether it is necessary to "eat" LF?
                break;
            }
            else
            {
                // Most likely it's just wrapping the text in the sentence to a new line.
                // Add a space so the words don't concatenate
                m_bufferedChar = result;
                result = Chars::kSpace;
                m_state = State::StreamingBufferedChar;
                break;
            }
        }
        else if ( m_state == State::EatingLeadingWhitespaces )
        {
            if ( result == Chars::kLineFeed )
            {
                m_state = State::EatingLineFeeds;
            }
            else if ( result != Chars::kSpace )
            {
                m_state = State::StreamingChar;
                break;
            }
        }
        else if ( m_state == State::StreamingChar )
        {
            if ( result == Chars::kLineFeed )
            {
                m_state = State::EatingLineFeeds;
            }
            else
            {
                break;
            }
        }
    }

    return result;
}

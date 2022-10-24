#pragma once

#include <Interfaces/Stream.hpp>

#include <optional>

namespace Minibook
{
    /**
     * @brief Removes LF symbols that are not paragraph separators from input stream
     */
    class LineUnwrapper final : public Stream<std::optional<wchar_t>>
    {
    public:
        using CharStream = Stream<std::optional<wchar_t>>;

        explicit LineUnwrapper( CharStream& source );

        /**
         * @return no value, if end of stream reached
         */
        virtual std::optional<wchar_t> Fetch() override;

    private:
        CharStream& m_source;

        enum class State
        {
            EatingLineFeeds,
            EatingLeadingWhitespaces,
            StreamingChar,
            StreamingBufferedChar
        };

        State m_state;
        State m_nextState;
        wchar_t m_bufferedChar;
    };

} // namespace Minibook

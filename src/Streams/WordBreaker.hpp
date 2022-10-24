#pragma once

#include <Interfaces/Stream.hpp>

#include <string>
#include <optional>

namespace Minibook
{
    /**
     * @brief Breaks the input stream of characters into tokens
     *
     * A lexeme is a group of characters that does not contain a space.
     */
    class WordBreaker final : public Stream<std::wstring>
    {
    public:
        using CharStream = Stream<std::optional<wchar_t>>;

        explicit WordBreaker( CharStream& source );

        /**
         * @return empty string, if end of stream reached
         */
        virtual std::wstring Fetch() override;

    private:
        CharStream& m_source;
    };
} // namespace Minibook

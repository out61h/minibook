#pragma once

#include <Interfaces/Stream.hpp>

#include <deque>
#include <map>
#include <string>
#include <vector>

namespace Minibook
{
    /**
     * @brief Breaks lexemes into syllables that can be hyphenated.
     */
    class WordHyphenator final : public Stream<std::wstring>
    {
    public:
        explicit WordHyphenator( Stream<std::wstring>& source );

        /**
         * @return empty string, if end of stream reached
         */
        virtual std::wstring Fetch() override;

    private:
        using ChunkList = std::deque<std::wstring>;
        using CharClasses = std::map<wchar_t, std::wstring>;
        using Rule = std::pair<std::wstring, int>;

        static ChunkList Split( std::wstring_view text, wchar_t separator );

        ChunkList Hyphenate( std::wstring word );

        Stream<std::wstring>& m_source;

        std::vector<Rule> m_rules;
        CharClasses m_classes;
        ChunkList m_chunks;
    };
} // namespace Minibook

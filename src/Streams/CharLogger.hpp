#pragma once

#include <Interfaces/Stream.hpp>

#include <fstream>
#include <optional>
#include <string>

namespace Minibook
{
    /**
     * @brief Passes a characters stream through itself unchanged and logs it to a file
     */
    class CharLogger final : public Stream<std::optional<wchar_t>>
    {
    public:
        CharLogger( Stream<std::optional<wchar_t>>& source,
                    std::string_view filename,
                    bool enabled );

        /**
         * @return no value, if end of stream reached
         */
        virtual std::optional<wchar_t> Fetch() override;

    private:
        Stream<std::optional<wchar_t>>& m_source;

        std::wofstream m_log;
    };
} // namespace Minibook

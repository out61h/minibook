#pragma once

#include <Interfaces/Stream.hpp>

#include <fstream>
#include <string>

namespace Minibook
{
    /**
     * @brief Passes a string stream through itself unchanged and logs it to a file
     */
    class StringLogger final : public Stream<std::wstring>
    {
    public:
        StringLogger( Stream<std::wstring>& source,
                      std::string_view filename,
                      bool enabled );

        /**
         * @return empty string, if end of stream reached
         */
        virtual std::wstring Fetch() override;

    private:
        Stream<std::wstring>& m_source;

        std::wofstream m_log;
    };
} // namespace Minibook

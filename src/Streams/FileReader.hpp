#pragma once

#include <Interfaces/Stream.hpp>

#include <fstream>
#include <optional>

namespace Minibook
{
    /**
     * @brief Reads octet stream from file
     */
    class FileReader final : public Stream<std::optional<uint8_t>>
    {
    public:
        explicit FileReader( const std::string& filename );

        /**
         * @return no value, if end of stream reached
         */
        virtual std::optional<uint8_t> Fetch() override;

        double GetProgress() const;

    private:
        std::ifstream m_input;
        std::uintmax_t m_size;
        std::uintmax_t m_read;
    };
} // namespace Minibook

#pragma once

#include <Interfaces/Stream.hpp>

#include <optional>

namespace Minibook
{
    /**
     * @brief Decodes wchar_t characters from a stream of UTF-8 octets
     */
    class UnicodeDecoder final : public Stream<std::optional<wchar_t>>
    {
    public:
        using OctetStream = Stream<std::optional<uint8_t>>;

        explicit UnicodeDecoder( OctetStream& source );

        /**
         * @return no value, if end of stream reached
         */
        virtual std::optional<wchar_t> Fetch() override;

    private:
        enum class State
        {
            ReadFirstOctet,
            ReadOneOctet,
            ReadTwoOctets,
            ReadThreeOctets,

            ExpectedBOM,
            ExpectedBB,
            ExpectedBF,

            Terminated,

            DetectedUTF8,

            Succeeded,
            Failed
        };

        OctetStream& m_source;
        State m_state;
    };
} // namespace Minibook

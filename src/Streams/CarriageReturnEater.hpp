#pragma once

#include <Interfaces/Stream.hpp>

#include <optional>

namespace Minibook
{
    /**
     * @brief Removes CR symbols from input stream
     */
    class CarriageReturnEater final : public Stream<std::optional<wchar_t>>
    {
    public:
        using CharStream = Stream<std::optional<wchar_t>>;

        explicit CarriageReturnEater( CharStream& source );

        /**
         * @return no value, if end of stream reached
         */
        virtual std::optional<wchar_t> Fetch() override;

    private:
        CharStream& m_source;
    };
} // namespace Minibook

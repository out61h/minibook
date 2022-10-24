#include "CarriageReturnEater.hpp"

#include "Constants/Chars.hpp"

using namespace Minibook;

CarriageReturnEater::CarriageReturnEater( CharStream& source )
    : m_source( source )
{
}

std::optional<wchar_t> CarriageReturnEater::Fetch()
{
    wchar_t result = 0;

    for ( ;; )
    {
        const auto character = m_source.Fetch();
        if ( !character )
            return {};

        result = *character;

        if ( result != Chars::kCarriageReturn )
            break;
    }

    return result;
}

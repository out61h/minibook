#pragma once

namespace Minibook
{
    struct Margin
    {
        Margin()
            : Top( 0. )
            , Right( 0. )
            , Bottom( 0. )
            , Left( 0. )
        {
        }

        Margin( double top, double right, double bottom, double left )
            : Top( top )
            , Right( right )
            , Bottom( bottom )
            , Left( left )
        {
        }

        double Top;
        double Right;
        double Bottom;
        double Left;
    };
} // namespace Minibook

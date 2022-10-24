#pragma once

namespace Minibook
{
    struct Size
    {
        Size()
            : Width( 0. )
            , Height( 0. )
        {
        }

        Size( double width, double height )
            : Width( width )
            , Height( height )
        {
        }

        double Width;
        double Height;
    };
} // namespace Minibook

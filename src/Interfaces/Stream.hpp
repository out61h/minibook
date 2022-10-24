#pragma once

namespace Minibook
{
    template<typename T>
    class Stream
    {
    public:
        virtual ~Stream() = default;

        virtual T Fetch() = 0;
    };
} // namespace Minibook

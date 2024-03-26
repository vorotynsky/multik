#pragma once

#include <memory>

namespace multik
{
    template <typename T>
    using Uniq = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Uniq<T> MakeUniq(Args&& ...args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Ref<T> MakeRef(Args&& ...args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Weak = std::weak_ptr<T>;
}

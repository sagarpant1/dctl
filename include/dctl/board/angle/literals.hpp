#pragma once
#include <dctl/board/angle/angle.hpp> // Angle

namespace dctl {
inline namespace literals {
inline namespace angle_literals {

constexpr auto operator"" _deg(unsigned long long n) noexcept
{
        return Angle{static_cast<int>(n)};
}

}       // namespace angle_literals
}       // namespace literals
}       // namespace dctl
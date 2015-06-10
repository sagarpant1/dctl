#pragma once
#include <dctl/angle.hpp>       // Angle
#include <cstddef>              // size_t
#include <stdexcept>            // invalid_argument
#include <tuple>                // forward_as_tuple

namespace dctl {
namespace board {

class Dimensions
{
        std::size_t width_, height_;
        bool inverted_;
public:
        constexpr Dimensions(std::size_t w, std::size_t h, bool i) noexcept
        :
                width_{w}, height_{h}, inverted_{i}
        {}

        constexpr auto width() const noexcept { return width_; }
        constexpr auto height() const noexcept { return height_; }
        constexpr auto inverted() const noexcept { return inverted_; }
};

constexpr auto operator==(Dimensions const& lhs, Dimensions const& rhs) noexcept
{
        return
               std::forward_as_tuple(lhs.width(), lhs.height(), lhs.inverted()) ==
               std::forward_as_tuple(rhs.width(), rhs.height(), rhs.inverted())
        ;
}

constexpr auto operator!=(Dimensions const& lhs, Dimensions const& rhs) noexcept
{
        return !(lhs == rhs);
}

constexpr auto ll_parity(Dimensions const& dim) noexcept
{
        return !dim.inverted();
}

constexpr auto ul_parity(Dimensions const& dim) noexcept
{
        return static_cast<bool>(dim.inverted() ^ (dim.height() % 2));
}

constexpr auto rotate(Dimensions const& dim, Angle a)
{
        switch (a) {
        case   0 : return dim;
        case  90 : return Dimensions{ dim.height(), dim.width (), static_cast<bool>((dim.width() % 2) ^                      !dim.inverted()) };
        case 180 : return Dimensions{ dim.width (), dim.height(), static_cast<bool>((dim.width() % 2) ^ (dim.height() % 2) ^  dim.inverted()) };
        case 270 : return Dimensions{ dim.height(), dim.width (), static_cast<bool>(                    (dim.height() % 2) ^ !dim.inverted()) };
        default  : return throw std::invalid_argument("Rotations of Dimensions objects shall be in multiples of 90 degrees."), dim;
        }
}

}       // namespace board
}       // namespace dctl

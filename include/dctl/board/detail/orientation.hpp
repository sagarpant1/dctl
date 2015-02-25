#pragma once
#include <dctl/angle.hpp>               // Angle, _deg
#include <dctl/board/dimensions.hpp>    // Dimensions, rotate
#include <dctl/board/grid.hpp>          // Grid
#include <xstd/algorithm.hpp>           // min_element
#include <xstd/iterator.hpp>            // cbegin, cend

namespace dctl {
namespace board {

template<int EdgeColumns>
struct grid_less
{
        Dimensions dim;

        constexpr auto rotated_grid_size(Angle const& theta) const
        {
                return Grid<EdgeColumns>{rotate(dim, theta)}.size();
        }

        constexpr auto operator()(Angle const& lhs, Angle const& rhs) const
        {
                return rotated_grid_size(lhs) < rotated_grid_size(rhs);
        }
};

template<int EdgeColumns>
constexpr auto size_minimizing_orientation(Dimensions const& dim)
{
        constexpr Angle orientations[] = { 0_deg, 90_deg, 180_deg, 270_deg };
        return Angle{*xstd::min_element(xstd::cbegin(orientations), xstd::cend(orientations), grid_less<EdgeColumns>{dim})};
}

}       // namespace board
}       // namespace dctl

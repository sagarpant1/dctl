#pragma once
#include <dctl/board/angle.hpp> // _deg, inverse, rotate
#include <dctl/color.hpp>       // white

namespace dctl {

template<class Board, Color ToMove, bool Reverse = false>
constexpr auto bearing_v = rotate(inverse(Board::orientation), ((ToMove == Color::white) ^ Reverse) ? 0_deg : 180_deg);

}       // namespace dctl
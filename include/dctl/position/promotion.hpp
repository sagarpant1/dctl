#pragma once
#include <dctl/board/mask.hpp>
#include <dctl/color.hpp>

namespace dctl {

template<class Board, Color ToMove>
bool is_promotion(std::size_t sq)
{
        auto constexpr promotion = board::Promotion<Board>::mask(ToMove);
        return promotion.test(sq);
}

}       // namespace dctl
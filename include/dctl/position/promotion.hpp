#pragma once
#include <dctl/board/mask.hpp>

namespace dctl {

template<bool Color, class Board>
bool is_promotion(std::size_t sq)
{
        auto constexpr promotion = board::Promotion<Board>::mask(Color);
        return promotion.test(sq);
}

}       // namespace dctl

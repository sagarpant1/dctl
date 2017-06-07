#pragma once
#include <dctl/core/board/mask/detail/fill.hpp>      // fill
#include <dctl/core/board/mask/detail/iterator.hpp>  // make_iterator
#include <dctl/core/rules/traits.hpp>                 // short_ranged_tag, long_ranged_tag
#include <iterator>                             // next

namespace dctl {
namespace core {
namespace board {
namespace mask {

template<class Board, int Direction, class KingRangeCategory>
struct push_targets;

template<class Board, int Direction>
struct push_targets<Board, Direction, short_ranged_tag>
{
        template<class Set>
        auto operator()(Set const active_pieces, Set const not_occupied) const noexcept
        {
                return Set(*std::next(detail::make_iterator<Board, Direction>(active_pieces))) & not_occupied;
        }
};

template<class Board, int Direction>
struct push_targets<Board, Direction, long_ranged_tag>
{
        template<class Set>
        auto operator()(Set const active_pieces, Set const not_occupied) const noexcept
        {
                return active_pieces ^ detail::fill<Board, Direction>{}(active_pieces, not_occupied);
        }
};

}       // namespace mask
}       // namespace board
}       // namespace core
}       // namespace dctl
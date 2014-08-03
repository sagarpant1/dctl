#pragma once
#include <dctl/rules/pool_fwd.hpp>      // Pool
#include <dctl/successor/value.hpp>     // Value (primary template)

namespace dctl {
namespace rules {

// http://americanpoolcheckers.us/americanpoolcheckers/index.php/history/apca-tournament-rules-of-play

struct Pool
{
        // main rules
        static constexpr auto is_long_ranged_king = true;                       // 15
        static constexpr auto is_backward_pawn_jump = true;                     // 13
        static constexpr auto is_jump_precedence = false;                       // 20

        // drawing rules
        static constexpr auto max_repetitions = 3;                              // 26
        static constexpr auto max_reversible_moves = 30;                        // 26
};

}       // namespace rules
}       // namespace dctl

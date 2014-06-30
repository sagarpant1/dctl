#pragma once
#include <dctl/rules/variants/thai_fwd.hpp>     // Thai
#include <dctl/rules/types/range.hpp>           // distance_1
#include <dctl/successor/value.hpp>             // Value (primary template)

namespace dctl {
namespace rules {

struct Thai
{
        // main rules
        static constexpr auto is_long_ranged_king = true;
        static constexpr auto is_backward_pawn_jump = false;
        static constexpr auto is_jump_precedence = false;

        // additional rules
        using range_land = range::distance_1;
        static constexpr auto is_en_passant_jump_removal = true;
        static constexpr auto initial_gap = 4;
};

}       // namespace rules
}       // namespace dctl

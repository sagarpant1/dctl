#pragma once
#include <dctl/rule_traits.hpp> // long_ranged_tag, passing_promotion_tag

namespace dctl {
namespace russian {

// http://www.shashist.ru/kodeks/kodeks2004.doc

struct Rules
{
        // required
        static constexpr auto is_backward_pawn_jump = true;     // 1.5.3
        using king_range_category = long_ranged_tag;            // 1.4.5

        // optional
        using promotion_category = passing_promotion_tag;       // 1.5.15

        // move
        static constexpr auto jumpsep = ':';
        static constexpr auto notation = Notation::algebraic;
};

}       // namespace russian
}       // namespace dctl
#pragma once

namespace dctl {
namespace rules {

// http://www.damweb.cz/pravidla/cdfull.html
struct Czech
{
        static constexpr auto is_algebraic_notation = true;     // 2.6
        static constexpr auto jumpsep = ':';

        static constexpr auto is_long_ranged_king = true;       // 3.9
        static constexpr auto is_backward_pawn_jump = false;    // 4.1
        static constexpr auto is_modality_precedence = true;    // 4.14

        struct precedence_tuple
        {
                template<class Action, class... State>
                constexpr auto operator()(Action const& a, State const&... s) const noexcept
                {
                        return a.is_with_king(s...);
                }
        };
};

}       // namespace rules
}       // namespace dctl

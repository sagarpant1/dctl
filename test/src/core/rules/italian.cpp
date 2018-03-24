//          Copyright Rein Halbersma 2010-2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <core/rules/precedence.hpp>         // precedence::is_consistent
#include <dctl/core/rules/italian.hpp>       // italian
#include <dctl/core/state/color_piece.hpp>         // king, pawn
#include <dctl/core/rules/type_traits.hpp>         // is_backward_pawn_jump, king_range_category, long_ranged_tag, is_trivial_precedence, is_superior_rank_jump, is_ordering, equal_to, less
#include <boost/test/unit_test.hpp>     // BOOST_AUTO_TEST_SUITE, BOOST_AUTO_TEST_CASE, BOOST_AUTO_TEST_SUITE_END
#include <vector>                       // vector

using namespace dctl::core;

BOOST_AUTO_TEST_SUITE(Rulesitalian)

using T = italian;

BOOST_AUTO_TEST_CASE(RuleTraits)
{
        static_assert(!is_backward_pawn_jump_v<T>);
        static_assert(!is_long_ranged_king_v<T>);

        static_assert(is_superior_rank_jump_v<T>);

        static_assert(!is_trivial_precedence_v<T>);
        static_assert(is_quantity_precedence_v<T>);
        static_assert(is_modality_precedence_v<T>);
        static_assert(is_contents_precedence_v<T>);
        static_assert(is_ordering_precedence_v<T>);

        struct Action
        {
                using rules_type [[maybe_unused]] = italian;
                int m_num_captured_pieces;
                int m_num_captured_kings;
                piece m_with;
                std::vector<int> m_piece_order;

                auto num_captured_pieces() const noexcept { return m_num_captured_pieces;  }
                auto num_captured_kings()  const noexcept { return m_num_captured_kings;   }
                auto is_with_king()        const noexcept { return m_with == piece::kings; }
                auto const& piece_order()  const noexcept { return m_piece_order;          }
        };

        auto const moves = std::vector<Action>
        {
                { 1, 0, piece::pawns, {      } },
                { 1, 0, piece::kings, {      } },
                { 1, 1, piece::kings, { 0    } },
                { 2, 0, piece::pawns, {      } },
                { 2, 0, piece::kings, {      } },
                { 2, 1, piece::kings, { 0    } },
                { 2, 1, piece::kings, { 1    } },
                { 2, 2, piece::kings, { 0, 1 } },
                { 3, 0, piece::pawns, {      } },
                { 3, 0, piece::kings, {      } },
                { 3, 1, piece::kings, { 0    } },
                { 3, 1, piece::kings, { 1    } },
                { 3, 1, piece::kings, { 2    } },
                { 3, 2, piece::kings, { 0, 1 } },
                { 3, 2, piece::kings, { 0, 2 } },
                { 3, 2, piece::kings, { 1, 2 } }
        };

        BOOST_CHECK(precedence::is_consistent(moves));
}

BOOST_AUTO_TEST_SUITE_END()

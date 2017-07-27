#pragma once

//          Copyright Rein Halbersma 2010-2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <dctl/util/type_traits.hpp>    // board_t, set_t
#include <tuple>                        // make_tuple
#include <type_traits>                  // decay_t

namespace dctl::core {
namespace block_adl {

// http://www.friesdammen.nl/dam/pagefr.php?articleID=20
struct frisian
{
        constexpr static auto width                     = 10;
        constexpr static auto height                    = 10;
        constexpr static auto is_inverted               = false;

        constexpr static auto is_backward_pawn_jump     = true;
        constexpr static auto is_long_ranged_king       = true;

        constexpr static auto is_orthogonal_jump        = true;
        constexpr static auto max_same_king_push        = 3;

        constexpr static auto is_quantity_precedence    = true;
        constexpr static auto is_contents_precedence    = true;
        constexpr static auto is_modality_precedence    = true;

        constexpr static auto precedence = [](auto const& a) {
                constexpr auto max_captured_pieces = set_t<board_t<std::decay_t<decltype(a)>>>::capacity();
                auto const num_captured_kings = a.num_captured_kings();
                return std::make_tuple(
                        (a.num_captured_pieces() + num_captured_kings) * max_captured_pieces - num_captured_kings,
                        a.is_with_king()
                );
        };
};

}       // namespace block_adl

using block_adl::frisian;

}       // namespace dctl::core

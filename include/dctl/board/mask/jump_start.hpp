#pragma once
#include <dctl/angle.hpp>                       // Angle, _deg, rotate, is_diagonal, is_up, is_down, is_left, is_right
#include <dctl/board/coordinates.hpp>           // ulo_from_sq
#include <dctl/board/mask/make_set_if.hpp>      // make_set_if
#include <dctl/set_type.hpp>                    // set_type
#include <dctl/utility/make_array.hpp>          // make_array
#include <array>                                // array
#include <cassert>                              // assert
#include <cstddef>                              // size_t

namespace dctl {
namespace board {

template<class Board>
class JumpStart
{
        // simulate a constexpr lambda (not allowed in C++14)
        struct lambda
        {
                int const segment_;

                constexpr auto operator()(int sq) const noexcept
                {
                        auto const alpha = rotate(segment_ * theta + beta, Board::orientation);
                        auto const offset = is_diagonal(alpha) ? 2 : 4;
                        auto const min_x = is_left(alpha) ? offset : 0;
                        auto const max_x = Board::width() - (is_right(alpha) ? offset : 0);
                        auto const min_y = is_up(alpha) ? offset : 0;
                        auto const max_y = Board::height() - (is_down(alpha) ? offset : 0);
                        auto const coord = to_ulo(sq, Board::outer_grid);
                        return
                                (min_x <= coord.x && coord.x < max_x) &&
                                (min_y <= coord.y && coord.y < max_y)
                        ;
                }
        };

        static constexpr auto init(int segment) noexcept
        {
                return make_set_if<Board>(lambda{segment});
        }

        static constexpr auto theta = Board::is_orthogonal_captures ? 45_deg : 90_deg;
        static constexpr auto beta  = Board::is_orthogonal_captures ?  0_deg : 45_deg;
        static constexpr auto N     = Board::is_orthogonal_captures ?      8 :      4;
        using Set = set_type<Board>;
        using table_type = std::array<Set, N>;

        static constexpr table_type table = make_array<N>(init);

public:
        static constexpr auto mask(Angle const& alpha) noexcept
        {
                auto const segment = (alpha - beta) / theta;
                assert(segment < N);
                return table[static_cast<std::size_t>(segment)];
        }
};

template<class Board>
constexpr Angle
JumpStart<Board>::theta;

template<class Board>
constexpr Angle
JumpStart<Board>::beta;

template<class Board>
constexpr typename JumpStart<Board>::table_type
JumpStart<Board>::table;

}       // namespace board
}       // namespace dctl
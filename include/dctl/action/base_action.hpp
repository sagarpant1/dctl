#pragma once
#include <dctl/color.hpp>
#include <dctl/piece.hpp>
#include <dctl/set_type.hpp>            // set_type
#include <dctl/utility/logic.hpp>
#include <cassert>                      // assert
#include <cstddef>                      // size_t

namespace dctl {
namespace detail {

template<class Rules, class Board>
class BaseAction
{
public:
        using board_type = Board;
        using rules_type = Rules;
        using   set_type = get_set_type<Board>;
        using square_type = std::size_t;

private:
        set_type captured_;
        square_type from_;
        square_type dest_;
        Color to_move_;
        Piece with_;
        Piece into_;

        constexpr auto invariant() const noexcept
        {
                return
                        util::implies(from() == dest(), is_jump()) /*&&
                        disjoint(captured(Piece::pawn), captured(Piece::king))*/
                ;
        }

public:
        BaseAction() = default;

        // pawn push
        constexpr BaseAction(std::size_t src, std::size_t dst, Color c, Piece promotion) noexcept
        :
                captured_{},
                from_{src},
                dest_{dst},
                to_move_{c},
                with_{Piece::pawn},
                into_{promotion}
        {
                assert(invariant());
        }

        // king push
        constexpr BaseAction(std::size_t src, std::size_t dst, Color c) noexcept
        :
                captured_{},
                from_{src},
                dest_{dst},
                to_move_{c},
                with_{Piece::king},
                into_{Piece::king}
        {
                assert(invariant());
        }

        // jump
        template<class Tracker>
        explicit constexpr BaseAction(Tracker const& t)
        :
                captured_{t.captured()},
                from_{t.from()},
                dest_{t.dest()},
                to_move_{t.to_move()},
                with_{t.with()},
                into_{t.into()}
        {
                assert(invariant());
        }

        constexpr auto captured() const noexcept
        {
                return captured_;
        }

        constexpr auto from() const noexcept
        {
                return from_;
        }

        constexpr auto dest() const noexcept
        {
                return dest_;
        }

        constexpr auto to_move() const noexcept
        {
                return to_move_;
        }

        constexpr auto is_to_move(Color c) const noexcept
        {
                return to_move() == c;
        }

        constexpr auto with() const noexcept
        {
                return with_;
        }

        constexpr auto is_with(Piece p) const noexcept
        {
                return with() == p;
        }

        constexpr auto into() const noexcept
        {
                return into_;
        }

        constexpr auto is_into(Piece p) const noexcept
        {
                return into() == p;
        }

        constexpr auto is_jump() const noexcept
        {
                return captured().any();
        }

        constexpr auto is_promotion() const noexcept
        {
                return is_with(Piece::pawn) && !is_into(Piece::pawn);
        }

        constexpr auto is_reversible() const noexcept
        {
                return is_with(Piece::king) && !is_jump();
        }

        constexpr auto num_captured() const noexcept
        {
                return captured().count();
        }
};

}       // namespace detail
}       // namespace dctl

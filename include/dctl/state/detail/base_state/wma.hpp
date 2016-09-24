#pragma once
#include <dctl/color.hpp>
#include <dctl/piece.hpp>
#include <dctl/utility/type_traits.hpp>         // set_t
#include <xstd/type_traits.hpp>                 // to_underlying_type

namespace dctl {
namespace detail {
namespace wma {
namespace block_adl {

template<class Board>
class base_state
{
public:
        using board_type = Board;
        using   set_type = set_t<Board>;

private:
        set_type white_;
        set_type pawns_;
        set_type pieces_;

public:
        base_state() = default;

        base_state(set_type const w, set_type const m, set_type const a) noexcept
        :
                white_{w},
                pawns_{m},
                pieces_{a}
        {}

        base_state(set_type const b, set_type const w, set_type const p, set_type const /* k */) noexcept
        :
                base_state{w, p, b | w}
        {}

        template<class Action>
        auto& make(Color const c, Action const& a)
        {
                pieces_.reset(a.from());
                pieces_.set  (a.dest());

                if (c == white_type{}) {
                        white_.reset(a.from());
                        white_.set  (a.dest());
                }

                if (a.with() == Piece::pawn)
                        pawns_.reset(a.from());

                if (a.into() == Piece::pawn)
                        pawns_.set(a.dest());

                if (a.is_jump()) {
                        pieces_ ^= a.captured_pieces();
                        white_ &= ~a.captured_pieces();
                        pawns_ &= ~a.captured_pieces();
                }

                return *this;
        }

        auto pieces(Color const c) const noexcept
        {
                return c == black_type{} ? pieces(black_type{}) : pieces(white_type{});
        }

        auto pieces(black_type) const noexcept
        {
                return pieces_ ^ white_;
        }

        auto pieces(white_type) const noexcept
        {
                return white_;
        }

        auto pieces(Piece const p) const noexcept
        {
                return p == pawn_type{} ? pieces(pawn_type{}) : pieces(king_type{});
        }

        auto pieces(pawn_type) const noexcept
        {
                return pawns_;
        }

        auto pieces(king_type) const noexcept
        {
                return pieces_ ^ pawns_;
        }

        auto pieces(Color const c, Piece const p) const noexcept
        {
                return c == black_type{} ?
                        (p == pawn_type{} ?  pieces(black_type{}, pawn_type{}) : pieces(black_type{}, king_type{})) :
                        (p == pawn_type{} ?  pieces(white_type{}, pawn_type{}) : pieces(white_type{}, king_type{}))
                ;
        }

        template<Piece Type>
        auto pieces(Color const c, piece_constant<Type>) const noexcept
        {
                return c == black_type{} ? pieces(black_type{}, Type) : pieces(white_type{}, Type);
        }

        template<Color Side>
        auto pieces(color_constant<Side>, Piece const p) const noexcept
        {
                return p == pawn_type{} ? pieces(Side, pawn_type{}) : pieces(Side, king_type{});
        }

        auto pieces(black_type, pawn_type) const noexcept
        {
                return ~white_ & pawns_;
        }

        auto pieces(black_type, king_type) const noexcept
        {
                return pieces_ ^ (white_ | pawns_);
        }

        auto pieces(white_type, pawn_type) const noexcept
        {
                return white_ & pawns_;
        }

        auto pieces(white_type, king_type) const noexcept
        {
                return white_ & ~pawns_;
        }

        auto pieces() const noexcept
        {
                return pieces_;
        }

        auto not_occupied() const noexcept
        {
                return mask::squares_v<board_type> ^ pieces();
        }

        auto num_pieces(Color const c, Piece const p) const noexcept
        {
                return pieces(c, p).count();
        }
};

}       // namespace block_adl

using block_adl::base_state;

}       // namespace wma
}       // namespace detail
}       // namespace dctl

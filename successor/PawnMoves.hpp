#pragma once
#include "Driver_fwd.hpp"
#include "Selection.hpp"
#include "../bit/Bit.hpp"
#include "../board/Direction.hpp"
#include "../node/Material.hpp"
#include "../node/Position.hpp"
#include "../node/Promotion.hpp"
#include "../node/Stack_fwd.hpp"
#include "../utility/Int2Type.hpp"
#include "../utility/IntegerTypes.hpp"
#include "../utility/NonConstructible.hpp"
#include "../utility/Shift.hpp"

namespace dctl {
namespace successor {

// partial specialization for pawn moves
template<bool Color, typename Rules, typename Board>
struct Driver<Color, Material::pawn, select::Moves, Rules, Board>
:
        private nonconstructible        // enforce static semantics
{
private:
        // typedefs
        typedef board::Direction<Color, Board> Direction;

public:
        static void generate(const Position<Board>& p, Stack& moves)
        {
                generate(p.pawns(Color), not_occupied(p), moves);
        }

        static int count(const Position<Board>& p)
        {
                return count(p.pawns(Color), not_occupied(p));
        }

        static bool detect(const Position<Board>& p)
        {
                return detect(p.pawns(Color), not_occupied(p));
        }

        static void generate(BitBoard active_pawns, BitBoard not_occupied, Stack& moves)
        {
                generate<Direction::left_up >(active_pawns, not_occupied, moves);
                generate<Direction::right_up>(active_pawns, not_occupied, moves);
        }

        static int count(BitBoard active_pawns, BitBoard not_occupied)
        {
                return (
                        count<Direction::left_up >(active_pawns, not_occupied) +
                        count<Direction::right_up>(active_pawns, not_occupied)
                );
        }

        static bool detect(BitBoard active_pawns, BitBoard not_occupied)
        {
                return (
                        detect<Direction::left_up >(active_pawns, not_occupied) ||
                        detect<Direction::right_up>(active_pawns, not_occupied)
                );
        }

private:
        // implementation
        template<int Index>
        static void generate(BitBoard active_pawns, BitBoard not_occupied, Stack& moves)
        {
                BitBoard from_sq, dest_sq;
                for (
                        active_pawns &= Pull<Board, Index>()(not_occupied);
                        active_pawns;
                        bit::clear_first(active_pawns)
                ) {
                        from_sq = bit::get_first(active_pawns);
                        dest_sq = Push<Board, Index>()(from_sq);
                        moves.push_back(
                                Move::create<Color>(
                                        from_sq ^ dest_sq,
                                        promotion_sq<Color, Board>(dest_sq)
                                )
                        );
                }
        }

        template<int Index>
        static int count(BitBoard active_pawns, BitBoard not_occupied)
        {
                return bit::count(
                        Sink<Board, Index, rules::scan_1>()(active_pawns, not_occupied)
                );
        }

        template<int Index>
        static bool detect(BitBoard active_pawns, BitBoard not_occupied)
        {
                return !bit::is_zero(
                        Sink<Board, Index, rules::scan_1>()(active_pawns, not_occupied)
                );
        }
};

}       // namespace successor
}       // namespace dctl

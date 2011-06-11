#include <cassert>
#include "Templates.h"
#include "../../Move/Stack.h"
#include "../../../Geometry/Direction.h"
#include "../../../Geometry/PushPull.h"
#include "../../../Utilities/Bit.h"

using namespace geometry::direction;

namespace tree {
namespace generate {
namespace capture { 

template<typename Rules, typename Board>
State<Rules, Board>::State(const node::Position<Board>& p)
:
        initial_targets_(passive_pieces(p)),
	remaining_targets_(initial_targets_),
	not_occupied_(p.not_occupied()),
        king_targets_(passive_kings(p)),
        from_sq_(0)
{
        init<Rules>()(current_);
        init<Rules>()(best_);
}

template<typename Rules, typename Board> template<size_t Index>
BitBoard State<Rules, Board>::targets(void) const
{
        return remaining_targets_ & Pull<Board, Index>()(path());
}

template<typename Rules, typename Board> template<size_t Index>
BitBoard State<Rules, Board>::path(void) const
{
        return path() & Board::JUMPABLE[Index];
}

template<typename Rules, typename Board>
BitBoard State<Rules, Board>::path(void) const
{
        return not_occupied_;
}

template<typename Rules, typename Board> template<bool Color>
BitBoard State<Rules, Board>::promotions(BitBoard dest_sq) const
{
        return dest_sq & Board::PROMOTION[Color][0];
}

template<typename Rules, typename Board>
BitBoard State<Rules, Board>::captured_targets(void) const
{
        return initial_targets_ ^ remaining_targets_;
}

// tag dispatching based on whether men can capture kings
template<typename Rules, typename Board>
BitBoard State<Rules, Board>::captured_kings(BitBoard captured_pieces) const
{
        return captured_kings(captured_pieces, Int2Type<variants::is_men_capture_kings<Rules>::value>());
}

// specialization for men that cannot capture kings
template<typename Rules, typename Board>
BitBoard State<Rules, Board>::captured_kings(BitBoard, Int2Type<false>) const
{
        return 0;
}

// specialization for men that can capture kings
template<typename Rules, typename Board>
BitBoard State<Rules, Board>::captured_kings(BitBoard captured_pieces, Int2Type<true>) const
{
        return captured_pieces & king_targets_;
}

template<typename Rules, typename Board> template<bool Color>
bool State<Rules, Board>::is_promotion(BitBoard dest_sq) const
{
        return !bit::is_zero(promotions<Color>(dest_sq));
}

template<typename Rules, typename Board>
bool State<Rules, Board>::is_promotion(void) const
{
        return current_.promotion;
}

template<typename Rules, typename Board>
bool State<Rules, Board>::current_greater_equal_best(void) const
{
        return greater_equal<Rules>()(current_, best_);
}

template<typename Rules, typename Board>
bool State<Rules, Board>::current_not_equal_to_best(void) const
{
        return not_equal_to<Rules>()(current_, best_);
}

template<typename Rules, typename Board>
void State<Rules, Board>::toggle_king_targets(void)
{
        initial_targets_ = remaining_targets_ ^= king_targets_;
}

template<typename Rules, typename Board>
void State<Rules, Board>::toggle_with_king(void)
{
        current_.with_king ^= true;
}

template<typename Rules, typename Board>
void State<Rules, Board>::toggle_promotion(void)
{
        current_.promotion ^= true;
}

template<typename Rules, typename Board>
void State<Rules, Board>::launch(BitBoard jump_sq)
{
        from_sq_ = jump_sq;
        not_occupied_ ^= jump_sq;
}

template<typename Rules, typename Board>
void State<Rules, Board>::finish(BitBoard jump_sq)
{
        not_occupied_ ^= jump_sq;
}

// tag dispatching on capture removal
template<typename Rules, typename Board>
void State<Rules, Board>::make(BitBoard target_sq)
{
        make(target_sq, Int2Type<variants::capture_removal<Rules>::value>());
}

// partial specialization for piece by piece removal during a capture sequence
template<typename Rules, typename Board>
void State<Rules, Board>::make(BitBoard target_sq, Int2Type<variants::REMOVE_1>)
{
        not_occupied_ ^= target_sq;
        make(target_sq, Int2Type<variants::REMOVE_N>());
}

// partial specialization for complete removal after a capture sequence
template<typename Rules, typename Board>
void State<Rules, Board>::make(BitBoard target_sq, Int2Type<variants::REMOVE_N>)
{
        remaining_targets_ ^= target_sq;
        increment<Rules>()(current_, target_sq, king_targets_);
}

// tag dispatching on capture removal
template<typename Rules, typename Board>
void State<Rules, Board>::undo(BitBoard target_sq)
{
        undo(target_sq, Int2Type<variants::capture_removal<Rules>::value>());
}

// partial specialization for piece by piece removal during a capture sequence
template<typename Rules, typename Board>
void State<Rules, Board>::undo(BitBoard target_sq, Int2Type<variants::REMOVE_1>)
{
        undo(target_sq, Int2Type<variants::REMOVE_N>());
        not_occupied_ ^= target_sq;
}

// partial specialization for complete removal after a capture sequence
template<typename Rules, typename Board>
void State<Rules, Board>::undo(BitBoard target_sq, Int2Type<variants::REMOVE_N>)
{
        decrement<Rules>()(current_, target_sq, king_targets_);
        remaining_targets_ ^= target_sq;
}

template<typename Rules, typename Board>
void State<Rules, Board>::improve_best(move::Stack& move_stack)
{
        copy<Rules>()(best_, current_);
        move_stack.clear();
}

// tag dispatching based on ambiguity of man captures
template<typename Rules, typename Board> template<bool Color>
void State<Rules, Board>::add_man_capture(BitBoard dest_sq, move::Stack& move_stack)
{
        add_man_capture<Color>(dest_sq, move_stack, Int2Type<variants::is_ambiguous_man_capture<Rules>::value>());
}

// partial specialization for man captures that are unambiguous
template<typename Rules, typename Board> template<bool Color>
void State<Rules, Board>::add_man_capture(BitBoard dest_sq, move::Stack& move_stack, Int2Type<false>)
{
        const BitBoard captured_pieces = captured_targets();
        move_stack.push<Color, Rules>(from_sq_ ^ dest_sq, promotions<Color>(dest_sq), captured_pieces, captured_kings(captured_pieces));
}

// partial specialization for man captures that can be ambiguous
template<typename Rules, typename Board> template<bool Color>
void State<Rules, Board>::add_man_capture(BitBoard dest_sq, move::Stack& move_stack, Int2Type<true>)
{
        const BitBoard captured_pieces = captured_targets();
        const bool ambiguous = !move_stack.empty() && large<Rules>()(current_, captured_pieces);
        move_stack.push<Color, Rules>(from_sq_ ^ dest_sq, promotions<Color>(dest_sq), captured_pieces, captured_kings(captured_pieces));
        if (ambiguous && move_stack.non_unique_top<Rules>())
                move_stack.pop();
}

// tag dispatching based on king halt after final capture
template<typename Rules, typename Board> template<bool Color, size_t Index>
void State<Rules, Board>::add_king_capture(BitBoard dest_sq, move::Stack& move_stack)
{
        add_king_capture<Color, Index>(dest_sq, move_stack, Int2Type<variants::king_capture_halt<Rules>::value>());
}

// partial specialization for kings that halt immediately if the final capture is a king, and slide through otherwise
template<typename Rules, typename Board> template<bool Color, size_t Index>
void State<Rules, Board>::add_king_capture(BitBoard dest_sq, move::Stack& move_stack, Int2Type<variants::HALT_K>)
{
        if (king_targets_ & Pull<Board, Index>()(dest_sq))
                add_king_capture<Color, Index>(dest_sq, move_stack, Int2Type<variants::HALT_1>());
        else
                add_king_capture<Color, Index>(dest_sq, move_stack, Int2Type<variants::HALT_N>());
}

// partial specialization for kings that halt immediately after the final capture
template<typename Rules, typename Board> template<bool Color, size_t Index>
void State<Rules, Board>::add_king_capture(BitBoard dest_sq, move::Stack& move_stack, Int2Type<variants::HALT_1>)
{
        const BitBoard captured_pieces = captured_targets();
        const bool ambiguous = !move_stack.empty() && large<Rules>()(current_, captured_pieces);
        add_king_capture<Color>(dest_sq, captured_pieces, captured_pieces & king_targets_, ambiguous, move_stack);
}

// partial specialization for kings that slide through after the final capture
template<typename Rules, typename Board> template<bool Color, size_t Index>
void State<Rules, Board>::add_king_capture(BitBoard dest_sq, move::Stack& move_stack, Int2Type<variants::HALT_N>)
{
        assert(dest_sq & path());

        const BitBoard captured_pieces = captured_targets();
        const BitBoard captured_kings = captured_pieces & king_targets_;
        const bool ambiguous = !move_stack.empty() && large<Rules>()(current_, captured_pieces);
        do {
                add_king_capture<Color>(dest_sq, captured_pieces, captured_kings, ambiguous, move_stack);
                PushAssign<Board, Index>()(dest_sq);
        } while (dest_sq & path());
}

// tag dispatching based on promotion condition
template<typename Rules, typename Board> template<bool Color>
void State<Rules, Board>::add_king_capture(BitBoard dest_sq, BitBoard captured_pieces, BitBoard captured_kings, bool ambiguous, move::Stack& move_stack)
{
        add_king_capture<Color>(dest_sq, captured_pieces, captured_kings, move_stack, Int2Type<variants::promotion_condition<Rules>::value>());
        if (ambiguous && move_stack.non_unique_top<Rules>())
                move_stack.pop();
}

// partial specialization for men that promote on the back row
template<typename Rules, typename Board> template<bool Color>
void State<Rules, Board>::add_king_capture(BitBoard dest_sq, BitBoard captured_pieces, BitBoard captured_kings, move::Stack& move_stack, Int2Type<variants::PROMOTE_BR>)
{
        move_stack.push<Color, Rules>(from_sq_ ^ dest_sq, captured_pieces, captured_kings);
}

// partial specialization for men that promote en-passant
template<typename Rules, typename Board> template<bool Color>
void State<Rules, Board>::add_king_capture(BitBoard dest_sq, BitBoard captured_pieces, BitBoard captured_kings, move::Stack& move_stack, Int2Type<variants::PROMOTE_EP>)
{
        if (!is_promotion())
                move_stack.push<Color, Rules>(from_sq_ ^ dest_sq,          captured_pieces, captured_kings);
        else
                move_stack.push<Color, Rules>(from_sq_ ^ dest_sq, dest_sq, captured_pieces, captured_kings);
}

}       // namespace capture
}       // namespace generate
}       // namespace tree

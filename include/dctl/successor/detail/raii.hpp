#pragma once
#include <dctl/piece.hpp>       // pawn, king
#include <cassert>              // assert
#include <cstddef>              // size_t

namespace dctl {
namespace successor {
namespace raii {

template<class Tracker>
class Launch
{
        Tracker& tracker;
public:
        ~Launch()
        {
                tracker.finish();
        }

        Launch(Launch const&) = delete;
        Launch& operator=(Launch const&) = delete;

        Launch(Tracker& t, std::size_t sq)
        :
                tracker{t}
        {
                tracker.launch(sq);
        }
};

template<class Tracker>
class Capture
{
        Tracker& tracker;
public:
        ~Capture()
        {
                tracker.release();
        }

        Capture(Capture const&) = delete;
        Capture& operator=(Capture const&) = delete;

        Capture(Tracker& t, std::size_t sq)
        :
                tracker{t}
        {
                tracker.capture(sq);
        }
};

template<class Tracker>
class Visit
{
        Tracker& tracker;
public:
        ~Visit()
        {
                tracker.leave();
        }

        Visit(Visit const&) = delete;
        Visit& operator=(Visit const&) = delete;

        Visit(Tracker& t, std::size_t sq)
        :
                tracker{t}
        {
                tracker.visit(sq);
        }
};

template<class Tracker>
class ToggleKingTargets
{
        Tracker& tracker;
public:
        ~ToggleKingTargets()
        {
                tracker.toggle_king_targets();
        }

        ToggleKingTargets(ToggleKingTargets const&) = delete;
        ToggleKingTargets& operator=(ToggleKingTargets const&) = delete;

        ToggleKingTargets(Tracker& t)
        :
                tracker{t}
        {
                tracker.toggle_king_targets();
        }
};

template<class Tracker>
class SetWithKing
{
        Tracker& tracker;
public:
        ~SetWithKing()
        {
                assert(tracker.is_with(Piece::king && tracker.is_into(Piece::pawn)));
                tracker.set_with(Piece::pawn);
                tracker.set_into(Piece::pawn);
        }

        SetWithKing(SetWithKing const&) = delete;
        SetWithKing& operator=(SetWithKing const&) = delete;

        SetWithKing(Tracker& t)
        :
                tracker{t}
        {
                assert(tracker.is_with(Piece::pawn) && tracker.is_into(Piece::pawn));
                tracker.set_with(Piece::king);
                tracker.set_into(Piece::king);
        }
};

template<class Tracker>
class SetPromotion
{
        Tracker& tracker;
public:
        ~SetPromotion()
        {
                assert(tracker.is_with(Piece::pawn) && tracker.is_into(Piece::king));
                tracker.set_into(Piece::pawn);
        }

        SetPromotion(SetPromotion const&) = delete;
        SetPromotion& operator=(SetPromotion const&) = delete;

        SetPromotion(Tracker& t)
        :
                tracker{t}
        {
                assert(tracker.is_with(Piece::pawn) && tracker.is_into(Piece::pawn));
                tracker.set_into(Piece::king);
        }
};

}       // namespace raii
}       // namespace successor
}       // namespace dctl

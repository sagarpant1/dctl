#pragma once
#include <functional>                   // function
#include <boost/utility.hpp>            // noncopyable
#include <dctl/successor/generation/generator_fwd.hpp>
#include <dctl/successor/generation/pawn_moves.hpp>
#include <dctl/successor/select.hpp>
#include <dctl/node/material.hpp>
#include <dctl/node/stack.hpp>
#include <dctl/node/unary_projections.hpp>

namespace dctl {
namespace successor {
namespace detail {

// partial specialization for pawn moves generation
template<bool Color, typename Position>
struct generator<Color, Material::pawn, Reverse, Position>
:
        // enforce reference semantics
        private boost::noncopyable,
        public std::function<void(Position const&)>
{
private:
        // typedefs

        typedef generator<!Color, Material::pawn, Moves, Position> PassivePawnMoves;

        // representation

        Stack& moves_;

public:
        // structors

        /*explicit*/ generator(Stack& m)
        :
                moves_(m)
        {}

        // function call operators

        void operator()(Position const& p) const
        {
                if (auto const active_pawns = p.pawns(Color))
                        PassivePawnMoves{moves_}.select(active_pawns, not_occupied(p));
        }
};

}       // namespace detail
}       // namespace successor
}       // namespace dctl

#pragma once
#include <functional>                   // function
#include "Enumerator_fwd.hpp"
#include "KingMoves.hpp"
#include "PawnMoves.hpp"
#include "../Select.hpp"
#include "../../node/Material.hpp"

namespace dctl {
namespace successor {
namespace detail {

template<bool Color, typename Position>
struct enumerator<Color, Material::both, Reverse, Position>
:
        public std::function<int(Position const&)>
{
private:
        // typedefs
        typedef enumerator<Color, Material::king, Reverse, Position> KingMoves;
        typedef enumerator<Color, Material::pawn, Reverse, Position> PawnMoves;

public:
        int operator()(Position const& p) const
        {
                return (
                        KingMoves()(p) +
                        PawnMoves()(p)
                );
        }
};

}       // namespace detail
}       // namespace successor
}       // namespace dctl

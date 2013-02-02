#pragma once
#include <dctl/successor/count/enumerator_fwd.hpp>
#include <dctl/successor/count/king_moves.hpp>
#include <dctl/successor/select/reverse.hpp>
#include <dctl/node/material.hpp>

namespace dctl {
namespace successor {
namespace detail {

template<bool Color, typename Position>
struct enumerator<Color, Material::king, select::reverse, Position>
:
        enumerator<Color, Material::king, Moves, Position>
{};

}       // namespace detail
}       // namespace successor
}       // namespace dctl

#pragma once

namespace dctl {
namespace grid {

template<int EdgeColumns>
class Grid;

template<>
class Grid<0>;

// primary template declaration
template<class Dimensions, int EdgeColumns>
class GridClass;

// partial template specialization declaration
template<class Dimensions>
class GridClass<Dimensions, 0>;

}       // namespace grid
}       // namespace dctl

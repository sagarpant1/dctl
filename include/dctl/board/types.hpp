#pragma once
#include <dctl/angle.hpp>               // _deg
#include <dctl/board/board.hpp>         // Board
#include <dctl/grid/dimensions.hpp>     // Dimensions

namespace dctl {
namespace board {

// square boards (fit into 64-bits, even with orthogonal capture)
using Micro             = Board< grid::Dimensions< 4,  4> >;
using Mini              = Board< grid::Dimensions< 6,  6> >;
using Checkers          = Board< grid::Dimensions< 8,  8> >;
using International     = Board< grid::Dimensions<10, 10> >;

// large boards (do not fit into 64-bits, even without orthogonal capture)
using Canadian          = Board< grid::Dimensions<12, 12> >;
using Dumm              = Board< grid::Dimensions<14, 14> >;

// lower left inverted square boards
using Roman             = Board< grid::Dimensions< 8,  8, true> >;
using SriLankan         = Board< grid::Dimensions<12, 12, true> >;

using Frisian           = International;

// rectangular boards
using Spantsireti08x10  = Board< grid::Dimensions< 8, 10> >;
using Spantsireti10x08  = Board< grid::Dimensions<10,  8> >;
using Spantsireti10x12  = Board< grid::Dimensions<10, 12> >;
using Spantsireti12x10  = Board< grid::Dimensions<12, 10> >;

using Ktar08x10         = Board< grid::Dimensions< 8, 10, true> >;
using Ktar10x08         = Board< grid::Dimensions<10,  8, true> >;
using Ktar10x11         = Board< grid::Dimensions<10, 11> >;
using Ktar10x12         = Board< grid::Dimensions<10, 12, true> >;
using Ktar12x10         = Board< grid::Dimensions<12, 10, true> >;

using Spantsireti       = Spantsireti10x08;

}       // namespace board
}       // namespace dctl

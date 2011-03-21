#pragma once
#include "Traits.h"

namespace Variants {

struct Thai {};

template<> struct man_capture_directions<Thai>          { enum { value = DIRS_UP  }; };
template<> struct king_capture_halt<Thai>               { enum { value = HALT_1   }; };
template<> struct capture_removal<Thai>                 { enum { value = REMOVE_1 }; };
template<> struct is_capture_direction_reversal<Thai>   { enum { value = true     }; };
template<> struct large_capture<Thai>                   { enum { value = 3        }; };

}       // namespace Variants

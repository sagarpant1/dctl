#pragma once
#include "Traits.h"

namespace variants {

// http://fpdamas.home.sapo.pt/regrasclass.htm
struct Spanish {};         

// move mechanics
template<> struct man_capture_directions<Spanish>       { enum { value = DIRS_UP }; };

// capture precedence
template<> struct is_majority_precedence<Spanish>       { enum { value = true    }; };

}       // namespace variants

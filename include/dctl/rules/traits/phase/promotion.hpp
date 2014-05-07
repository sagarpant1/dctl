#pragma once
#include <dctl/rules/types/phase.hpp>   // apres_fini
#include <boost/tti/member_type.hpp>    // BOOST_TTI_TRAIT_MEMBER_TYPE

namespace dctl {
namespace rules {

BOOST_TTI_TRAIT_MEMBER_TYPE(promotion_phase, promotion_phase)

template<class Rules, class Default = apres_fini>
using promotion_phase_t = typename promotion_phase<Rules, Default>::type;

}       // namespace rules
}       // namespace dctl

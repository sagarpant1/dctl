#include <dctl/rules/traits/is_backward_pawn_jump.hpp>  // is_backward_pawn_jump_v
#include <dctl/rules/variants.hpp>
#include <boost/mpl/vector.hpp>                         // vector
#include <boost/test/test_case_template.hpp>            // BOOST_AUTO_TEST_CASE_TEMPLATE
#include <boost/test/unit_test.hpp>                     // BOOST_AUTO_TEST_SUITE, BOOST_AUTO_TEST_SUITE_END

namespace dctl {
namespace rules {

BOOST_AUTO_TEST_SUITE(RulesTraitsIsBackwardPawnJump)

typedef boost::mpl::vector<
        Checkers, Czech, Italian, Spanish, Thai
> VariantsFalse;

BOOST_AUTO_TEST_CASE_TEMPLATE(NotIsBackwardPawnJumpV, T, VariantsFalse)
{
        static_assert(!is_backward_pawn_jump_v<T>, "");
}

typedef boost::mpl::vector<
        AKWDamme, Frisian, HHoogland, International, Killer, Pool, Russian
> VariantsTrue;

BOOST_AUTO_TEST_CASE_TEMPLATE(IsBackwardPawnJumpV, T, VariantsTrue)
{
        static_assert(is_backward_pawn_jump_v<T>, "");
}

BOOST_AUTO_TEST_SUITE_END()

}       // namespace rules
}       // namespace dctl

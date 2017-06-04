#include <core/board/group.hpp>                      // action::is_realized, make
#include <core/board/sequence.hpp>                   // micro, mini, checkers, Roman, spantsiretti, international, frisian, ktar<10, 11>,
                                                // ktar<10, 12>, Compact_10_12, Compact_12_10, rectangular<12, 10>, canadian, srilankan, dumm
#include <dctl/core/board/angle.hpp>                 // _deg, inverse, rotate
#include <dctl/core/board/detail/dimensions.hpp>     // dimensions
#include <boost/algorithm/cxx11/all_of.hpp>     // all_of
#include <boost/test/test_case_template.hpp>    // BOOST_AUTO_TEST_CASE_TEMPLATE
#include <boost/test/unit_test.hpp>             // BOOST_AUTO_TEST_SUITE, BOOST_AUTO_TEST_SUITE_END, BOOST_CHECK
#include <type_traits>                          // common_type
#include <vector>                               // vector

using namespace dctl::core;
using namespace board::literals;

BOOST_AUTO_TEST_SUITE(Griddimensions)

BOOST_AUTO_TEST_CASE_TEMPLATE(GroupActionIsRealizedForAllCyclicGroupsOnAlldimensions, T, board::BoardSequence)
{
        auto const op = [](auto i, auto j){ return rotate(i, j); };
        auto const inv = [](auto i){ return inverse(i); };

        auto const C1 = board::make_group(
                { 0_deg },
                op, inv
        );

        auto const C2 = board::make_group(
                { 0_deg, 180_deg },
                op, inv
        );

        auto const C4 = board::make_group(
                { 0_deg,  90_deg, 180_deg, 270_deg },
                op, inv
        );

        using CyclicGroup = std::common_type_t<decltype(C1), decltype(C2), decltype(C4)>;

        auto const C_N = std::vector<CyclicGroup>
        {
                C1, C2, C4
        };

        auto const dim = board::detail::dimensions{ T::width, T::height, T::is_inverted };

        BOOST_CHECK(
                boost::algorithm::all_of(C_N, [&](auto const& g) {
                        return board::group::action::is_realized(dim, g);
                })
        );
}

BOOST_AUTO_TEST_SUITE_END()

#include <dctl/egdb/index.hpp>          // subdatabase
#include <dctl/core/board.hpp>               // rectangular
#include <dctl/core/rules.hpp>               // international
#include <dctl/core/state.hpp>               // state
#include <dctl/util/type_traits.hpp> // position_t
#include <boost/test/unit_test.hpp>     // BOOST_AUTO_TEST_SUITE, BOOST_AUTO_TEST_CASE, BOOST_CHECK_EQUAL, BOOST_AUTO_TEST_SUITE_END
#include <vector>                       // vector

using namespace dctl::egdb;
using namespace dctl::core;

BOOST_AUTO_TEST_SUITE(Index)

BOOST_AUTO_TEST_CASE(NumeralIsInverseOfPosition)
{
        using rules_type = international;
        using board_type = board::rectangular<6, 6>;
        using state_type = state<rules_type, board_type>;

        using subdivision_type = subdivision<position_t<state_type>>;
        auto const subdivisions = std::vector<subdivision_type>
        {
                { 4, 0, 0, 0 },
                { 4, 0, 4, 0 },
                { 0, 4, 0, 0 },
                { 0, 4, 0, 4 },
                { 2, 2, 0, 0 },
                { 2, 2, 2, 0 },
                { 2, 2, 0, 2 },
                { 2, 2, 2, 2 },
                { 4, 0, 2, 0 },
                { 0, 4, 0, 2 },
                { 2, 2, 1, 1 }
        };

        for (auto const& subdb : subdivisions) {
                for (auto n = 0LL; n < subdb.size(); ++n) {
                        if (auto const p = subdb.position(n)) {
                                BOOST_CHECK_EQUAL(subdb.index(p.value()), n);
                        }
                }
        }
}

BOOST_AUTO_TEST_SUITE_END()

#include <cstdint>
#include <boost/mpl/vector.hpp>                 // vector
#include <boost/test/unit_test.hpp>             // BOOST_AUTO_TEST_SUITE, BOOST_CHECK, BOOST_CHECK_EQUAL, BOOST_CHECK_EQUAL_COLLECTIONS, BOOST_AUTO_TEST_SUITE_END
#include <boost/test/test_case_template.hpp>    // BOOST_AUTO_TEST_CASE_TEMPLATE
#include <dctl/bit/set.hpp>                     // Set

#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/algorithm/adjacent_find.hpp>
#include <boost/range/algorithm_ext/is_sorted.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/end.hpp>
#include <dctl/egdb/index.hpp>
#include <iostream>
#include <iomanip>
#include <boost/range/irange.hpp>
#include <dctl/board/types.hpp>
#include <dctl/board/mask.hpp>

namespace dctl {
namespace egdb {

BOOST_AUTO_TEST_SUITE(EndgameDatabaseIndex)

using U = int;

using SetTypes = boost::mpl::vector
<
        bit::Set<U, uint64_t, 1>
>;

BOOST_AUTO_TEST_CASE_TEMPLATE(ColexSubsetRank, T, SetTypes)
{
        constexpr auto b = T{ 0, 1, 2 };
        constexpr auto N = T{}.max_size();
        constexpr auto e = T{ N - 2, N - 1 };

        BOOST_CHECK_EQUAL(colex::combination_rank(b), 0);
        BOOST_CHECK_EQUAL(colex::combination_rank(e), (BinomialTable<N, 10>::coefficient(N, e.size())) - 1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ColexSubsetUnRank, T, SetTypes)
{
        using Binomial = BinomialTable<>;
        auto const N = 50;
        auto const K = 7;
        auto const b = std::ptrdiff_t{0};
        auto const e = Binomial::coefficient(N, K);

        using Board = board::International;
        //auto const ghosts = ~board::Squares<Board>::mask();

        for (auto i : boost::irange(b, e)) {
                auto pos = colex::combination_unrank({N, K}, i);
                //auto const pos = obstr::back_inserted(colex::combination_unrank({N, K}, i), ghosts);
                // generate successors etc.
                //auto const idx = colex::combination_rank(obstr::back_erased(pos, ghosts));
                auto const idx = colex::combination_rank(pos);
                BOOST_CHECK_EQUAL(idx, i);
        }
}

BOOST_AUTO_TEST_SUITE_END()

}       // namespace egdb
}       // namespace dctl

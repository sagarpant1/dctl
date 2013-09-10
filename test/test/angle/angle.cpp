#include <algorithm>                            // any_of
#include <boost/iterator/counting_iterator.hpp> // counting_iterator
#include <boost/test/unit_test.hpp>             // BOOST_AUTO_TEST_SUITE, BOOST_AUTO_TEST_SUITE_END, BOOST_AUTO_TEST_CASE, BOOST_CHECK
#include <dctl/angle/angle.hpp>                 // is_angle, make_angle
#include <dctl/angle/degrees.hpp>               // D360

namespace dctl {
namespace angle {

BOOST_AUTO_TEST_SUITE(AngleAngle)

BOOST_AUTO_TEST_CASE(MakeAngleIsAngle)
{
        auto const alpha = boost::counting_iterator<int>(-2 * angle::D360);
        auto const omega = boost::counting_iterator<int>( 2 * angle::D360 + 1);

        BOOST_CHECK(
                std::all_of(alpha, omega, [](int const& i){
                        return is_angle(make_angle(i));
                })
        );
}

BOOST_AUTO_TEST_SUITE_END()

}       // namespace angle
}       // namespace dctl

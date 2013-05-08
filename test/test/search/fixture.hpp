#pragma once
#include <string>                       // string
#include <utility>                      // pair
#include <boost/test/unit_test.hpp>
#include <dctl/search/root.hpp>
#include <dctl/search/objective.hpp>
#include <dctl/node/position.hpp>
#include <dctl/setup/setup.hpp>
#include <dctl/board/types.hpp>
#include <dctl/rules/variants.hpp>

namespace dctl {
namespace search {

template<typename Position, typename Objective>
struct Fixture
{
        Fixture()
        {
                root_.resize_hash(4096);
        }

        ~Fixture()
        {
                root_.resize_hash(1);
        }

        typedef std::pair<std::string, int> FEN_depth;
        typedef typename Position::rules_type Rules;
        typedef typename Position::board_type Board;

        template<std::size_t N>
        void run(FEN_depth const (&tests)[N])
        {
                for (auto const& t: tests) {
                        root_.clear_hash();
                        auto const position = setup::read<Rules, Board, pdn::protocol>()(t.first);
                        auto const value = root_.analyze(position, t.second);
                        BOOST_CHECK_EQUAL(win_value(t.second), value);
                }
        }

        Root<Position, Objective> root_;
};

typedef GameObjective<NoMovesLeft> DefaultObjective;

}       // namespace search
}       // namespace dctl

#pragma once
#include <dctl/core/state/dxp.hpp>
#include <string>
#include <variant>
#include <vector>

namespace dctl::core {
namespace dxp {

struct Fixture
{
        factory
        <
                dxp::game_request,
                dxp::game_acknowledge,
                dxp::move,
                dxp::back_request,
                dxp::back_acknowledge,
                dxp::game_end,
                dxp::chat
        > f;

        struct visitor
        {
                std::vector<std::string>& data;

                template<class T>
                auto operator()(T const& value) { data.push_back(value.str()); }

                auto operator()(std::monostate) {}
        };

        std::vector<std::string> parsed;
        visitor vis{parsed};
};

}        // namespace dxp
}        // namespace dctl::core

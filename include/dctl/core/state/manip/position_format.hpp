#pragma once
#include <ios>          // xalloc
#include <ostream>      // iword

namespace dctl {
namespace core {
namespace manip {

enum class StateFormat { diag = 1, fen = 2 };

inline
auto position_format()
{
        static auto const slot = std::ios_base::xalloc();
        return slot;
}

}       // namespace manip

template<class CharT, class Traits>
auto& diag(std::basic_ostream<CharT, Traits>& ostr)
{
        ostr.iword(manip::position_format()) = static_cast<int>(manip::StateFormat::diag);
        return ostr;
}

template<class CharT, class Traits>
auto& fen(std::basic_ostream<CharT, Traits>& ostr)
{
        ostr.iword(manip::position_format()) = static_cast<int>(manip::StateFormat::fen);
        return ostr;
}

}       // namespace core
}       // namespace dctl

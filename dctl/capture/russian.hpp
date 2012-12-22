#pragma once
#include <boost/operators.hpp>          // totally_ordered
#include <dctl/capture/value_fwd.hpp>   // Value (primary template)
#include <dctl/rules/russian_fwd.hpp>   // Russian

namespace dctl {
namespace capture {

// partial specialization for Russian draughts
template<typename Board>
struct Value<rules::Russian, Board>
:
        // Curiously Recurring Template Pattern (CRTP)
        private boost::totally_ordered< Value<rules::Russian, Board> >  // < >= > <= == !=
{
public:
        // structors

        Value()
        :
                promotion_(false)
        {
                BOOST_ASSERT(invariant());
        }

        // modifiers

        void toggle_promotion()
        {
                promotion_ ^= true;
                BOOST_ASSERT(invariant());
        }

        // queries

        bool is_promotion() const
        {
                return promotion_;
        }

        // predicates

        // operator>=, operator>, operator<= automatically generated by boost::totally_ordered
        friend bool operator<(Value const & /* lhs */, Value const& /* rhs */)
        {
                return false;
        }

        // operator!= automatically generated by boost::totally_ordered
        friend bool operator==(Value const & /* lhs */, Value const& /* rhs */)
        {
                return true;
        }

private:
        bool invariant() const
        {
                return true;
        }

        // representation

        bool promotion_;
};

}       // namespace capture
}       // namespace dctl

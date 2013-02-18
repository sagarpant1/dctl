#pragma once
#include <cstddef>                      // size_t
#include <limits>                       // numeric_limits
#include <tuple>                        // tie
#include <boost/assert.hpp>             // BOOST_ASSERT
#include <boost/operators.hpp>          // totally_ordered
#include <dctl/successor/value_fwd.hpp> // Value (primary template)
#include <dctl/rules/spanish_fwd.hpp>   // Spanish

namespace dctl {
namespace successor {

// specialization for Spanish draughts
template<>
struct Value<rules::Spanish>
:
        // Curiously Recurring Template Pattern (CRTP)
        private boost::totally_ordered< Value<rules::Spanish> > // < >= > <= == !=
{
public:
        // structors

        Value()
        :
                num_pieces_(0),
                num_kings_(0)
        {
                BOOST_ASSERT(invariant());
        }

        // modifiers

        void increment(bool is_king)
        {
                BOOST_ASSERT(!full());
                num_kings_ += is_king;
                ++num_pieces_;
                BOOST_ASSERT(invariant());
        }

        void decrement(bool is_king)
        {
                BOOST_ASSERT(!empty());
                --num_pieces_;
                num_kings_ -= is_king;
                BOOST_ASSERT(invariant());
        }

        // queries

        std::size_t count() const
        {
                return num_pieces_;
        }

        // predicates

        // operator>=, operator>, operator<= automatically generated by boost::totally_ordered
        friend bool operator<(Value const& lhs, Value const& rhs)
        {
                // delegate to std::tuple::operator<
                return (
                        std::tie(lhs.num_pieces_, lhs.num_kings_) <
                        std::tie(rhs.num_pieces_, rhs.num_kings_)
                );
        }

        // operator!= automatically generated by boost::totally_ordered
        friend bool operator==(Value const& lhs, Value const& rhs)
        {
                // delegate to std::tuple::operator==
                return (
                        std::tie(lhs.num_pieces_, lhs.num_kings_) ==
                        std::tie(rhs.num_pieces_, rhs.num_kings_)
                );
        }

private:
        // predicates

        bool invariant() const
        {
                return (
                        num_kings_ <= num_pieces_ &&
                        num_pieces_ <= std::numeric_limits<std::size_t>::max()
                );
        }

        bool empty() const
        {
                return 0 == num_kings_ && num_kings_ == num_pieces_;
        }

        bool full() const
        {
                return num_pieces_ == std::numeric_limits<std::size_t>::max();
        }

        // representation

        std::size_t num_pieces_;
        std::size_t num_kings_;
};

}       // namespace successor
}       // namespace dctl

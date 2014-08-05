#pragma once
#include <dctl/angle.hpp>               // Angle
#include <dctl/utility/shift.hpp>       // shift_assing
#include <dctl/type_traits.hpp>
#include <boost/operators.hpp>          // totally_ordered, unit_steppable

namespace dctl {
namespace wave {

template<class Board, int Direction>
class Cursor
:       boost::totally_ordered< Cursor<Board, Direction>        // != >= > <=
,       boost::unit_steppable < Cursor<Board, Direction>        // ++, --
> >
{
        static constexpr auto theta = Angle{Direction};
        static constexpr auto S = Board::shift_size(theta);
        static constexpr auto N = is_positive(theta) ? -S : S;
        static_assert(N != 0, "Cursors need a non-zero stride.");

        using Set = set_type_t<Board>;

public:
        // constructors

        Cursor() = default;

        explicit Cursor(Set const& c) noexcept
        :
                cursor_{c}
        {}

        template<class, int>
        friend class Cursor;

        template<int M>
        Cursor(Cursor<Board, M> const& other) noexcept
        :
                cursor_{other.cursor_}
        {}

        // modifiers

        // operator++(int) provided by boost::unit_steppable
        auto& operator++() noexcept
        {
                util::shift_assign<is_positive(theta)>{}(cursor_, S);
                return *this;
        }

        // operator--(int) provided by boost::unit_steppable
        auto& operator--() noexcept
        {
                util::shift_assign<is_negative(theta)>{}(cursor_, S);
                return *this;
        }

        // queries

        /* implicit */ operator Set() const noexcept
        {
                return cursor_;
        }

private:
        // representation

        Set cursor_{};
};

}       // namespace wave
}       // namespace dctl

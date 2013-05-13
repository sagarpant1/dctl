#pragma once
#include <string>                       // string
#include <dctl/dxp/i_message.hpp>       // IMessage
#include <dctl/factory/mixin.hpp>       // FactoryCreate

namespace dctl {
namespace dxp {

/*

        The format and semantics of Chat are defined at:
        http://www.mesander.nl/damexchange/echat.htm

*/

class Chat final
:
        // Curiously Recurring Template Pattern (CRTP)
        public mixin::FactoryCreate<'C', Chat, IMessage>
{
public:
        // structors

        explicit Chat(std::string const& message)
        :
                text_ { message }
        {}

        // queries

        std::string text() const
        {
                return text_;
        }

        // output

        static std::string str(std::string const& message)
        {
                return identifier() + body(message);
        }

private:
        // virtual implementation

        virtual std::string do_header() const override
        {
                return identifier();
        }

        virtual std::string do_body() const override
        {
                return body(text());
        }

        static std::string body(std::string const& m)
        {
                return m;
        }

        // representation

        std::string text_;
};

}       // namespace dxp
}       // namespace dctl

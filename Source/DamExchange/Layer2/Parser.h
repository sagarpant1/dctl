#pragma once
#include <map>
#include <memory>
#include <string>
#include "AbstractMessage.h"

namespace DamExchange {
namespace Layer2 {

class Parser
{
public:
        // typedefs
        typedef std::shared_ptr<AbstractMessage> (*Creator)(const std::string&);

        static std::shared_ptr<AbstractMessage> find(const std::string&);
        static bool insert(const std::string&, Creator);
        static bool erase(const std::string&);

private:
        //  enforce singleton semantics 
        Parser(void);
        Parser(const Parser&);
        Parser& operator=(const Parser&);
        ~Parser(void);

        // implementation
        typedef std::map<std::string, Creator> CreatorMap;
        static CreatorMap& instance(void);
};

}       // namespace Layer2
}       // namespace DamExchange

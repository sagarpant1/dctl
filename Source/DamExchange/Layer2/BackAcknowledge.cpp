#include <cassert>
#include <iomanip>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include "BackAcknowledge.h"
#include "Parser.h"

namespace DXP = damexchange;

const std::string DXP::layer2::BackAcknowledge::HEADER = "K";

const bool DXP::layer2::BackAcknowledge::REGISTERED = Parser::insert(HEADER, create);

std::shared_ptr<DXP::layer2::AbstractMessage> DXP::layer2::BackAcknowledge::create(const std::string& msg)
{
        return std::make_shared<BackAcknowledge>(msg);
}

DXP::layer2::BackAcknowledge::BackAcknowledge(const std::string& msg)
:
        acceptance_code_(static_cast<AcceptanceCode>(boost::lexical_cast<size_t>(msg.substr(0, 1).c_str())))
{
}

DXP::layer2::BackAcknowledge::BackAcknowledge(AcceptanceCode a)
:
        acceptance_code_(a)
{
}

DXP::layer2::BackAcknowledge::AcceptanceCode DXP::layer2::BackAcknowledge::acceptance_code(void) const
{
        return acceptance_code_;
}

std::string DXP::layer2::BackAcknowledge::header(void) const
{
        return HEADER;
}

std::string DXP::layer2::BackAcknowledge::body(void) const
{
        std::stringstream sstr;
        sstr << std::setw( 1) << acceptance_code();
        return sstr.str();
}

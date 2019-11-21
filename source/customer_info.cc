#include "customer_info.h"

#include <functional>
#include <regex>

#include "class_registration.h"

namespace inventory {

namespace {

using Rule = std::function<bool(const std::string&)>;

#define DEF_PASSPORT_RULE(location, rule) DEF_PASSPORT_RULE_HELPER(__COUNTER__, location, rule)
#define DEF_PASSPORT_RULE_HELPER(count, location, rule) static ClassRegister<Location, Rule> rule##count(location, rule)

bool ruleOfBrazil(const std::string& passport_id) {
  static std::regex reg("^B[0-9]{3}[A-Z]{2}[A-Z|0-9]{7}$");
  return std::regex_match(passport_id, reg);
}

bool ruleOfArgentina(const std::string& passport_id) {
  static std::regex reg("^A[A-Z]{2}[A-Z|0-9]{9}$");
  return std::regex_match(passport_id, reg);
}

DEF_PASSPORT_RULE(Brazil, ruleOfBrazil);
DEF_PASSPORT_RULE(Argentina, ruleOfArgentina);

}  // namespace

CustomerInfo::CustomerInfo() : passport_id() {
}

CustomerInfo::CustomerInfo(const std::string& id) : passport_id(id) {
}

bool CustomerInfo::isFrom(const Location location) const {
  auto rule = ClassRepos<Location, Rule>::instance().lookup(location);
  return rule != nullptr ? (*rule)(passport_id) : false;
}

}  // namespace inventory

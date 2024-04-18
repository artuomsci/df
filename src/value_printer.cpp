#include "value_printer.h"

using namespace df;

ValuePrinter::ValuePrinter(const Value &value) : m_value(value) {}

std::string ValuePrinter::toString() const {
  const auto &type = m_value.type();
  if (type == typeid(std::string)) {
    return std::any_cast<std::string>(m_value);
  } else if (type == typeid(int64_t)) {
    return std::to_string(std::any_cast<int64_t>(m_value));
  } else if (type == typeid(double)) {
    return std::to_string(std::any_cast<double>(m_value));
  }

  return "";
}

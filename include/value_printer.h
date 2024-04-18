#pragma once

#include <string>

#include "value.h"

namespace df {
class ValuePrinter {
public:
  ValuePrinter(const Value &value);
  std::string toString() const;

private:
  const Value &m_value;
};
} // namespace df

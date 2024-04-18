#pragma once

#include <chrono>

#include "actor.h"
#include "value.h"

namespace df {
class ImpulseGeneratorActor : public Actor {
public:
  ImpulseGeneratorActor(const Value &value,
                        const std::chrono::milliseconds &period,
                        const std::string &label = "");

private:
  Value m_value;
  std::chrono::milliseconds m_period;
  std::chrono::time_point<std::chrono::steady_clock> m_startTime{};
};
}

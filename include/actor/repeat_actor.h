#pragma once

#include <string>

#include "actor.h"

namespace df {
class RepeatActor : public Actor {
public:
  RepeatActor(size_t count, const std::string &label = "");

  size_t count() const;

private:
  size_t m_count{};
};
} // namespace df

#pragma once

#include <string>

#include "actor.h"

namespace df {

class PrintActor : public Actor {
public:
  PrintActor(const std::string &label = "");
};

} // namespace df

#pragma once

#include <optional>
#include <vector>

#include "actor/actor_fwd.h"

namespace df {
class RateBalanceSolver {
public:
  RateBalanceSolver(const std::vector<PtrActor> &actors);
};
} // namespace df

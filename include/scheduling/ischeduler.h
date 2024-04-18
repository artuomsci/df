#pragma once

#include <memory>
#include <vector>

#include "actor/actor_fwd.h"

namespace df {

class IScheduler {
public:
  virtual ~IScheduler(){};
  virtual void addActor(const PtrActor &actor) = 0;
  virtual void addActors(const std::vector<PtrActor> &actors) = 0;
  virtual void run() = 0;
  virtual void stop() = 0;
};

using PtrIScheduler = std::shared_ptr<IScheduler>;

} // namespace df

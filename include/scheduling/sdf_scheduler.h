#pragma once

#include <atomic>
#include <memory>
#include <thread>
#include <vector>

#include "actor/actor_fwd.h"
#include "ischeduler.h"

namespace df {

class Toposort;

/**
 * @brief Static dataflow scheduler
 */
class SDFScheduler : public IScheduler {
public:
  ~SDFScheduler();
  void addActor(const PtrActor &actor) override;
  void addActors(const std::vector<PtrActor> &actors) override;
  void run() override;
  void stop() override;

private:
  std::shared_ptr<Toposort> m_toposort;
  std::thread m_runThread;
  std::atomic<bool> m_isStopRun{true};
};

} // namespace df

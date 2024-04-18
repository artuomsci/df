#pragma once

#include <atomic>
#include <deque>
#include <thread>
#include <vector>

#include "actor/actor_fwd.h"
#include "ischeduler.h"

namespace df {

/**
 * @brief Dynamic dataflow scheduler
 */
class DDFScheduler : public IScheduler {
public:
  ~DDFScheduler();
  void addActor(const PtrActor &actor) override;
  void addActors(const std::vector<PtrActor> &actors) override;
  void run() override;
  void stop() override;

private:
  std::deque<PtrActor> m_actors;
  std::thread m_runThread;
  std::atomic<bool> m_isStopRun{true};
};

} // namespace df

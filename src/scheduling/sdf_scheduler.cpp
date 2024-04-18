#include "scheduling/sdf_scheduler.h"

#include "actor/actor.h"
#include "scheduling/toposort.h"

using namespace df;

SDFScheduler::~SDFScheduler() { stop(); }

void SDFScheduler::addActor(const PtrActor &actor) {
  if (!m_toposort) {
    m_toposort = std::make_shared<Toposort>();
  }

  m_toposort->addActor(actor);
}

void SDFScheduler::addActors(const std::vector<PtrActor> &actors) {
  if (!m_toposort) {
    m_toposort = std::make_shared<Toposort>();
  }

  for (const auto &actor : actors) {
    m_toposort->addActor(actor);
  }
}

void SDFScheduler::run() {
  if (!m_toposort || !m_isStopRun) {
    return;
  }

  auto sortedActors = m_toposort->sort();

  m_isStopRun = false;

  m_runThread = std::thread([sortedActors, this]() {
    while (!m_isStopRun) {
      std::deque<PtrActor> stub;
      std::for_each(sortedActors.begin(), sortedActors.end(),
                    [&](const PtrActor &actor) { actor->fire(stub); });
    }
  });
}

void SDFScheduler::stop() {
  m_isStopRun = true;
  if (m_runThread.joinable()) {
    m_runThread.join();
  }
}

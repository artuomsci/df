#include "scheduling/ddf_scheduler.h"

#include "actor/actor.h"

using namespace df;

DDFScheduler::~DDFScheduler() { stop(); }

void DDFScheduler::addActor(const PtrActor &actor) {
  m_actors.push_back(actor);
}

void DDFScheduler::addActors(const std::vector<PtrActor> &actors) {
  for (const PtrActor &actor : actors) {
    m_actors.push_back(actor);
  }
}

void DDFScheduler::run() {
  if (!m_isStopRun) {
    return;
  }

  m_isStopRun = false;

  m_runThread = std::thread([this]() {
    while (!m_isStopRun && !m_actors.empty()) {
      auto &current = m_actors.front();
      for (size_t i = 0; i < current->fireRate(); ++i) {
        current->fire(m_actors);
      }

      if (current->inputCount() == 0) {
        m_actors.push_back(current);
      }

      m_actors.pop_front();
    }
  });
}

void DDFScheduler::stop() {
  m_isStopRun = true;
  if (m_runThread.joinable()) {
    m_runThread.join();
  }
}

#pragma once

#include <list>

#include "actor/actor_fwd.h"
#include "algo/topological_sort.h"

namespace df {

class Toposort {
public:
  ~Toposort();
  void addActor(const PtrActor &actor);
  std::list<PtrActor> sort();

private:
  using Node = TopologicalSort<PtrActor>::Node *;

  Node findNode(const PtrActor &actor) const;

  std::list<Node> m_nodes;
};
} // namespace df

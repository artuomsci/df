#include "scheduling/toposort.h"

#include "actor/actor.h"
#include "buffer.h"

using namespace df;

Toposort::~Toposort() {
  std::for_each(m_nodes.begin(), m_nodes.end(), [](Node node) { delete node; });
}

void Toposort::addActor(const PtrActor &actor) {
  auto node = new TopologicalSort<PtrActor>::Node;
  node->userdata = actor;
  m_nodes.push_back(node);
}

Toposort::Node Toposort::findNode(const PtrActor &actor) const {
  auto it = std::find_if(
      m_nodes.begin(), m_nodes.end(),
      [&actor](const auto &element) { return element->userdata == actor; });

  if (it != m_nodes.end()) {
    return *it;
  }

  return nullptr;
}

std::list<PtrActor> Toposort::sort() {
  for (const auto &node : m_nodes) {

    auto &actor = node->userdata;

    for (const auto &[_, buffer] : actor->inputs()) {
      if (auto src = buffer->source().lock()) {

        if (auto bindNode = findNode(src)) {
          node->inputs.insert(bindNode);
        }
      }
    }

    for (const auto &[_, buffer] : actor->outputs()) {
      if (auto tgt = buffer->target().lock()) {

        if (auto bindNode = findNode(tgt)) {
          node->outputs.insert(bindNode);
        }
      }
    }
  }

  TopologicalSort<PtrActor> tpSort;
  tpSort.setNodes(m_nodes);

  std::list<PtrActor> ret;

  auto inputNodes = tpSort.sort();
  std::transform(inputNodes.begin(), inputNodes.end(), std::back_inserter(ret),
                 [](const auto &node) { return node->userdata; });

  return ret;
}

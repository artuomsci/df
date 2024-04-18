#pragma once

#include <list>
#include <set>

namespace df {

template <typename T> class TopologicalSort {
public:
  struct Node {
    std::set<Node *> inputs;
    std::set<Node *> outputs;
    T userdata;
  };

  void setNodes(const std::list<Node *> &nodes) { m_nodes = nodes; }
  void addNode(Node *node) { m_nodes.push_back(node); }

  std::list<Node *> sort() {
    std::list<Node *> ret;

    auto init = m_nodes;

    while (!init.empty()) {
      for (auto it = init.begin(); it != init.end();) {
        if ((*it)->inputs.empty()) {
          ret.push_back(*it);

          for (const auto &child : (*it)->outputs) {
            child->inputs.erase(*it);
          }

          it = init.erase(it);
        } else {
          ++it;
        }
      }
    }

    return ret;
  }

private:
  std::list<Node *> m_nodes;
};
} // namespace df

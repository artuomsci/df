#pragma once

#include <deque>
#include <memory>

#include "actor/actor_fwd.h"
#include "value.h"

namespace df {

class Buffer : public std::enable_shared_from_this<Buffer> {
public:
  Buffer() = default;
  ~Buffer();

  void setSource(Port index, const WeakPtrActor &src);
  WeakPtrActor source() const;
  Port sourcePort() const;
  void setTarget(Port index, const WeakPtrActor &tgt);
  WeakPtrActor target() const;
  Port targetPort() const;

  const Value &operator[](size_t pos);

  bool empty() const;
  const Value &value() const;
  void pop();
  void clear();
  void push(const Value &val);
  size_t size() const;
  void moveDataTo(Buffer &other);

private:
  std::deque<Value> m_data;
  WeakPtrActor m_src;
  Port m_sourcePort{};
  WeakPtrActor m_tgt;
  Port m_targetPort{};
};

} // namespace df

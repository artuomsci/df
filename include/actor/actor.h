#pragma once

#include <deque>
#include <functional>
#include <string>
#include <vector>

#include "actor_fwd.h"
#include "buffer_fwd.h"
#include "scheduling/ischeduler.h"

namespace df {

class Actor {
public:
  using Func = std::function<void(BufferPack &, BufferPack &)>;
  using Bind = std::pair<Port, PtrBuffer>;

  Actor(size_t inputsCount, size_t outputsCount, const std::string &label = "");
  virtual ~Actor();
  void fire(std::deque<PtrActor> &next);
  void attachInput(Port index, const PtrBuffer &buffer);
  void attachOutput(Port index, const PtrBuffer &buffer);
  size_t inputCount() const;
  size_t outputCount() const;
  std::vector<Bind> inputs() const;
  std::vector<Bind> outputs() const;
  void setFunction(const Func &fn);
  const std::string &label() const;
  void setConsumeRate(Port index, size_t rate);
  size_t consumeRate(Port index) const;
  void setProduceRate(Port index, size_t rate);
  size_t produceRate(Port index) const;
  size_t fireRate() const;
  void setFireRate(size_t rate);

  static void connect(const PtrActor &src, Port srcPort, const PtrActor &dst,
                      Port dstPort);

protected:
  static void moveBufferPack(BufferPack &src, BufferPack &dst);

  bool isReady() const;

  Func m_function;

  BufferPack m_inputs;
  BufferPack m_inputsInternal;
  std::vector<size_t> m_consumeRates;

  std::vector<Bind> m_outputs;
  BufferPack m_outputsInternal;
  std::vector<size_t> m_produceRates;

  std::string m_label;

  size_t m_fireRate{1};
};

} // namespace df

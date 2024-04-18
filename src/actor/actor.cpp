#include "actor/actor.h"

#include "buffer.h"

using namespace df;

Actor::Actor(size_t inputsCount, size_t outputsCount, const std::string &label)
    : m_label(label) {
  m_inputs.resize(inputsCount);
  m_inputsInternal.resize(inputsCount);
  std::for_each(m_inputsInternal.begin(), m_inputsInternal.end(),
                [](PtrBuffer &buffer) { buffer = std::make_shared<Buffer>(); });

  m_consumeRates.resize(inputsCount);

  m_outputsInternal.resize(outputsCount);
  std::for_each(m_outputsInternal.begin(), m_outputsInternal.end(),
                [](PtrBuffer &buffer) { buffer = std::make_shared<Buffer>(); });

  m_produceRates.resize(outputsCount);
}

Actor::~Actor() {}

void Actor::fire(std::deque<PtrActor> &next) {

  if (!isReady()) {
    return;
  }

  moveBufferPack(m_inputs, m_inputsInternal);

  m_function(m_inputsInternal, m_outputsInternal);

  for (auto &[index, buffer] : m_outputs) {

    auto &output = *m_outputsInternal[index];

    for (size_t i = 0; i < output.size(); ++i) {
      buffer->push(output[i]);

      if (auto target = buffer->target().lock()) {
        if (target->isReady()) {
          next.push_back(target);
        }
      }
    }
  }

  for (auto &buffer : m_outputsInternal) {
    buffer->clear();
  }
}

void Actor::attachInput(Port index, const PtrBuffer &buffer) {
  m_inputs[index] = buffer;
}

void Actor::attachOutput(Port index, const PtrBuffer &buffer) {
  m_outputs.emplace_back(index, buffer);
}

size_t Actor::inputCount() const { return m_inputsInternal.size(); }

size_t Actor::outputCount() const { return m_outputsInternal.size(); }

std::vector<Actor::Bind> Actor::inputs() const {
  std::vector<Bind> ret;
  for (size_t i = 0; i < m_inputs.size(); ++i) {
    ret.emplace_back(i, m_inputs[i]);
  }
  return ret;
}

std::vector<Actor::Bind> Actor::outputs() const { return m_outputs; }

void Actor::setFunction(const Func &fn) { m_function = fn; }

const std::string &Actor::label() const { return m_label; }

void Actor::setConsumeRate(Port index, size_t rate) {
  m_consumeRates[index] = rate;
}

size_t Actor::consumeRate(Port index) const { return m_consumeRates[index]; }

void Actor::setProduceRate(Port index, size_t rate) {
  m_produceRates[index] = rate;
}

size_t Actor::produceRate(Port index) const { return m_produceRates[index]; }

void Actor::connect(const PtrActor &src, Port srcPort, const PtrActor &dst,
                    Port dstPort) {
  auto buffer = std::make_shared<Buffer>();
  buffer->setSource(srcPort, src);
  buffer->setTarget(dstPort, dst);
}

void Actor::moveBufferPack(BufferPack &src, BufferPack &dst) {
  auto itSrc = src.begin();
  auto itDst = dst.begin();

  while (itSrc != src.end()) {
    (*itSrc)->moveDataTo(*(*itDst));
    ++itSrc;
    ++itDst;
  }
}

bool Actor::isReady() const {
  return !std::any_of(m_inputs.begin(), m_inputs.end(),
                      [](const PtrBuffer &buffer) { return buffer->empty(); });
}

size_t Actor::fireRate() const { return m_fireRate; }

void Actor::setFireRate(size_t rate) { m_fireRate = rate; }

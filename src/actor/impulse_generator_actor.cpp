#include "actor/impulse_generator_actor.h"

#include "buffer.h"

using namespace df;
using namespace std::chrono;

ImpulseGeneratorActor::ImpulseGeneratorActor(
    const Value &value, const std::chrono::milliseconds &period,
    const std::string &label)
    : Actor(0, 1, label), m_value(value), m_period(period) {
  m_startTime = steady_clock::now();

  m_function = [this](BufferPack &input, BufferPack &output) {
    auto current = steady_clock::now();
    auto diff = current - m_startTime;
    if (diff >= m_period) {
      for (size_t i = 0; i < produceRate(0); ++i) {
        output[0]->push(m_value);
      }

      m_startTime = current;
    }
  };
}

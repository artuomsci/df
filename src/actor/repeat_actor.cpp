#include "actor/repeat_actor.h"

#include "buffer.h"

using namespace df;

RepeatActor::RepeatActor(size_t count, const std::string &label)
    : Actor(1, 1, label), m_count(count) {
  m_function = [this](BufferPack &input, BufferPack &output) {
    for (size_t i = 0; i < m_count; ++i) {
      output[0]->push(input[0]->value());
    }
  };
}

size_t RepeatActor::count() const { return m_count; }

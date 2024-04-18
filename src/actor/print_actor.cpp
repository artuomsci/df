#include "actor/print_actor.h"

#include <cstdint>
#include <iostream>
#include <string>

#include "buffer.h"
#include "value_printer.h"

using namespace df;

PrintActor::PrintActor(const std::string &label) : Actor(1, 1, label) {
  m_function = [](BufferPack &input, BufferPack &output) {
    std::for_each(input.begin(), input.end(),
                  [&output](PtrBuffer &inputBuffer) {
                    auto &in = (*inputBuffer);

                    for (size_t i = 0; i < inputBuffer->size(); ++i) {
                      std::cout << ValuePrinter(in[i]).toString() << std::endl;

                      output[i]->push(in[i]);
                    }
                  });
  };
}

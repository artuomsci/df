#pragma once

#include <any>
#include <cstdint>
#include <iostream>

#include "actor/print_actor.h"
#include "buffer.h"
#include "scheduling/sdf_scheduler.h"

namespace df {

void sdf_test() {

  auto sched = std::make_shared<SDFScheduler>();

  auto incr = std::make_shared<Actor>(2, 2);
  incr->setFunction([](BufferPack &input, BufferPack &output) {
    auto value = std::any_cast<int64_t>(input[0]->value()) +
                 std::any_cast<int64_t>(input[1]->value());

    output[0]->push(value);
    output[1]->push(std::any_cast<int64_t>(input[0]->value()));
  });

  auto div = std::make_shared<Actor>(1, 1);
  div->setFunction([](BufferPack &input, BufferPack &output) {
    auto value = std::any_cast<int64_t>(input.front()->value()) / int64_t(2);

    output[0]->push(value);
  });

  auto mlt = std::make_shared<Actor>(1, 1);
  mlt->setFunction([](BufferPack &input, BufferPack &output) {
    auto value = std::any_cast<int64_t>(input.front()->value()) * int64_t(4);

    output[0]->push(value);
  });

  auto printDiv = std::make_shared<PrintActor>();
  auto printMlt = std::make_shared<PrintActor>();

  auto input0 = std::make_shared<Buffer>();
  input0->push(int64_t(4));

  auto input1 = std::make_shared<Buffer>();
  input1->push(int64_t(2));

  input0->setTarget(0, incr);
  input1->setTarget(1, incr);

  Actor::connect(incr, 0, div, 0);
  Actor::connect(incr, 1, mlt, 0);

  Actor::connect(div, 0, printDiv, 0);
  Actor::connect(mlt, 0, printMlt, 0);

  sched->addActors({div, incr, mlt, printDiv, printMlt});

  sched->run();

  while (true) {
    std::string input;
    std::cin >> input;

    if (input == "q") {
      sched->stop();
      break;
    }
  }
}

} // namespace df

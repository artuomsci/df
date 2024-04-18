#pragma once

#include <any>
#include <assert.h>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>

#include "actor/actor.h"
#include "actor/impulse_generator_actor.h"
#include "buffer.h"
#include "scheduling/rate_balance_solver.h"

namespace df {

void rate_solver_test() {

  // 1 --> 2
  {
    auto gen = std::make_shared<ImpulseGeneratorActor>(
        int64_t(4), std::chrono::milliseconds(100), "gen");
    gen->setProduceRate(0, 1);

    auto mlt = std::make_shared<Actor>(1, 1, "mlt");
    mlt->setConsumeRate(0, 2);
    mlt->setFunction([](BufferPack &input, BufferPack &output) {
      auto value = std::any_cast<int64_t>(input.front()->value()) * int64_t(4);

      output[0]->push(value);
    });

    Actor::connect(gen, 0, mlt, 0);

    std::vector<PtrActor> actors{gen, mlt};

    RateBalanceSolver solver(actors);

    assert(gen->fireRate() == 2);
    assert(mlt->fireRate() == 1);
  }

  // 2 --> 1
  {
    auto gen = std::make_shared<ImpulseGeneratorActor>(
        int64_t(4), std::chrono::milliseconds(100), "gen");
    gen->setProduceRate(0, 2);

    auto mlt = std::make_shared<Actor>(1, 1, "mlt");
    mlt->setConsumeRate(0, 1);
    mlt->setFunction([](BufferPack &input, BufferPack &output) {
      auto l = std::any_cast<int64_t>(input[0]->value());
      auto r = std::any_cast<int64_t>(input[1]->value());
      output[0]->push(l * r);
    });

    Actor::connect(gen, 0, mlt, 0);

    std::vector<PtrActor> actors{gen, mlt};

    RateBalanceSolver solver(actors);

    assert(gen->fireRate() == 1);
    assert(mlt->fireRate() == 2);
  }

  // 2 --> 1|1 --> 4
  {
    auto gen = std::make_shared<ImpulseGeneratorActor>(
        int64_t(4), std::chrono::milliseconds(100), "gen");
    gen->setProduceRate(0, 2);

    auto mlt = std::make_shared<Actor>(1, 1, "mlt");
    mlt->setConsumeRate(0, 1);
    mlt->setProduceRate(0, 1);
    mlt->setFunction([](BufferPack &input, BufferPack &output) {
      auto value = std::any_cast<int64_t>(input.front()->value()) * int64_t(4);

      output[0]->push(value);
    });

    auto div = std::make_shared<Actor>(1, 1, "div");
    div->setConsumeRate(0, 4);
    div->setProduceRate(0, 1);
    div->setFunction([](BufferPack &input, BufferPack &output) {
      auto value = std::any_cast<int64_t>(input.front()->value()) / int64_t(2);

      output[0]->push(value);
    });

    Actor::connect(gen, 0, mlt, 0);
    Actor::connect(mlt, 0, div, 0);

    std::vector<PtrActor> actors{gen, mlt, div};

    RateBalanceSolver solver(actors);

    assert(gen->fireRate() == 2);
    assert(mlt->fireRate() == 4);
    assert(div->fireRate() == 1);
  }

  {
    // 8 --> 2
    // 1 --> 4
    auto x0 = std::make_shared<ImpulseGeneratorActor>(
        int64_t(2), std::chrono::milliseconds(100), "x0");
    x0->setProduceRate(0, 8);

    auto x1 = std::make_shared<ImpulseGeneratorActor>(
        int64_t(2), std::chrono::milliseconds(100), "x1");
    x1->setProduceRate(0, 1);

    auto mlt = std::make_shared<Actor>(2, 1, "mlt");
    mlt->setConsumeRate(0, 2);
    mlt->setConsumeRate(1, 4);
    mlt->setFunction([](BufferPack &input, BufferPack &output) {
      auto value = std::any_cast<int64_t>(input.front()->value()) * int64_t(4);

      output[0]->push(value);
    });

    Actor::connect(x0, 0, mlt, 0);
    Actor::connect(x1, 0, mlt, 1);

    std::vector<PtrActor> actors{x0, x1, mlt};

    RateBalanceSolver solver(actors);

    assert(x0->fireRate() == 1);
    assert(x1->fireRate() == 16);
    assert(mlt->fireRate() == 4);
  }
}

} // namespace df

#include "scheduling/rate_balance_solver.h"

#include <exception>

#include "actor/actor.h"
#include "algo/numerical.h"
#include "algo/slau_gauss_solver.h"
#include "buffer.h"

using namespace df;

RateBalanceSolver::RateBalanceSolver(const std::vector<PtrActor> &actors) {

  bool isUpdate{true};
  while (isUpdate) {
    isUpdate = false;
    for (size_t srcInd = 0; srcInd < actors.size(); ++srcInd) {

      const auto &srcActor = actors[srcInd];

      for (const auto &[_, buffer] : srcActor->outputs()) {
        if (auto tgtActor = buffer->target().lock()) {

          auto srcProduceRate = srcActor->produceRate(buffer->sourcePort());
          auto tgtConsumeRate = tgtActor->consumeRate(buffer->targetPort());

          auto mlt = lcm(srcProduceRate, tgtConsumeRate);
          auto l_mlt = srcActor->fireRate() * srcProduceRate;
          auto r_mlt = tgtActor->fireRate() * tgtConsumeRate;

          mlt = std::max(mlt, r_mlt);
          mlt = std::max(mlt, l_mlt);

          auto newScrFireRate = mlt / srcProduceRate;
          auto newTgtFireRate = mlt / tgtConsumeRate;

          if (srcActor->fireRate() != newScrFireRate) {
            srcActor->setFireRate(newScrFireRate);
            isUpdate = true;
          }

          if (tgtActor->fireRate() != newTgtFireRate) {
            tgtActor->setFireRate(newTgtFireRate);
            isUpdate = true;
          }
        }
      }
    }
  }
}

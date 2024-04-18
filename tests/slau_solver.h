#pragma once

#include <assert.h>
#include <iostream>

#include "algo/slau_gauss_solver.h"

namespace df {
void slau_solver_test() {

  SLAUGaussSolver::Row row0{3.0, 2.0, -4.0, 3.0};
  SLAUGaussSolver::Row row1{2.0, 3.0, 3.0, 15.0};
  SLAUGaussSolver::Row row2{5.0, -3.0, 1.0, 14.0};

  SLAUGaussSolver::Matrix mat{row0, row1, row2};

  SLAUGaussSolver ge(mat);

  auto solution = ge.solution();
  assert(std::abs(solution[0] - 3.0) < 0.001);
  assert(std::abs(solution[1] - 1.0) < 0.001);
  assert(std::abs(solution[2] - 2.0) < 0.001);
}
} // namespace df

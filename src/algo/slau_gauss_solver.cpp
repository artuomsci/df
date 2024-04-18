#include "algo/slau_gauss_solver.h"

#include <cstdint>

using namespace df;

SLAUGaussSolver::SLAUGaussSolver(Matrix mat) : m_solution(mat.size()) {

  if (mat.empty()) {
    return;
  }

  elimination(mat);

  for (int64_t i = mat.size() - 1; i >= 0; --i) {

    double sum{};
    for (size_t j = i + 1; j < mat.size(); ++j) {
      sum += mat[i][j] * m_solution[j];
    }

    m_solution[i] = (mat[i].back() - sum) / mat[i][i];
  }
}

const SLAUGaussSolver::Row &SLAUGaussSolver::solution() const {
  return m_solution;
}

void SLAUGaussSolver::elimination(Matrix &mat) {
  if (mat.size() < 2) {
    return;
  }

  for (size_t p = 0; p < mat.size() - 1; ++p) {
    auto &src_row = mat[p];

    for (size_t i = p + 1; i < mat.size(); ++i) {
      auto &dst_row = mat[i];

      auto k = dst_row[p] / src_row[p];

      for (size_t j = p; j < src_row.size(); ++j) {
        dst_row[j] -= src_row[j] * k;
      }
    }
  }
}

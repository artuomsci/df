#pragma once

#include <vector>

namespace df {
class SLAUGaussSolver {
public:
  using Row = std::vector<double>;
  using Matrix = std::vector<Row>;

  SLAUGaussSolver(Matrix mat);
  const Row &solution() const;

private:
  void elimination(Matrix &mat);
  SLAUGaussSolver::Row m_solution;
};
} // namespace df

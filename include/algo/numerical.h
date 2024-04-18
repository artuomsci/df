#pragma once

#include <cstdint>

namespace df {

/**
 * @brief Greatest common divisor
 */
uint64_t gcd(uint64_t left, uint64_t right) {
  if (right == 0) {
    return left;
  }
  return gcd(right, left % right);
}

/**
 * @brief Least common multiple
 */
uint64_t lcm(uint64_t left, uint64_t right) {
  return (left * right) / gcd(left, right);
}

} // namespace df

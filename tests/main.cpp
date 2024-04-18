#include <cstring>

#include "ddf.h"
#include "rate_balance.h"
#include "sdf.h"
#include "slau_solver.h"

using namespace std;
using namespace df;

int main(int argc, char *argv[]) {

  sdf_test();
  ddf_test();
  slau_solver_test();
  rate_solver_test();

  return 0;
}

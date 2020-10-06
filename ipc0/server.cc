#include <l4/sys/cxx/ipc_epiface>
#include <l4/re/util/object_registry>
#include <l4/re/util/br_manager>
#include <l4/re/env>
#include <l4/re/util/cap_alloc>
#include <stdio.h>

#include "ipc_interface.h"

class Calculator : public L4::Epiface_t<Calculator, Calc>
{
  public:
  int op_add(Calc::Rights, l4_int32_t a, l4_int32_t b, l4_int32_t &result) const
  {
    result = a + b;
    return 0;
  }

  int op_sub(Calc::Rights, l4_int32_t a, l4_int32_t b, l4_int32_t &result) const
  {
    result = a - b;
    return 0;
  }

  int op_mul(Calc::Rights, l4_int32_t a, l4_int32_t b, l4_int32_t &result) const
  {
    result = a * b;
    return 0;
  }

  int op_div(Calc::Rights, l4_int32_t a, l4_int32_t b, l4_int32_t &result) const
  {
    if (b == 0)
      return -1;

    result = a / b;
    return 0;
  }
};

L4Re::Util::Registry_server<L4Re::Util::Br_manager_hooks> server;


int main()
{
  static Calculator calculator;

  // Register server
  if (!server.registry()->register_obj(&calculator, "calc_server").is_valid())
  {
    printf("Could not register service, is there 'calc_server' in caps table?\n");
    return 1;
  }

  printf("Welcome to calculator server\nUse add, sub, mul, div\n");
  
  // Wait for client requests
  server.loop();

  return 0;
}
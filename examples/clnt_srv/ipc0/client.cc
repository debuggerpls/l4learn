#include <l4/re/util/cap_alloc>
#include <l4/re/env>
#include <l4/sys/types.h>

#include <stdio.h>

#include "ipc_interface.h"

int error_msg(const char* str);
void result_for(l4_int32_t a, l4_int32_t b, l4_int32_t result, const char* str);

int main()
{
  L4::Cap<Calc> server = L4Re::Env::env()->get_cap<Calc>("calc_server");
  if (!server.is_valid())
    return error_msg("Could not get server capability!");

  for (l4_int32_t a = 1; a < 10; ++a)
  {
    l4_int32_t b = 10 - a;
    l4_int32_t result = 0;

    if (server->add(a, b, &result))
      return error_msg("add");
    
    result_for(a, b, result, "add");

    if (server->sub(a, b, &result))
      return error_msg("sub");

    result_for(a, b, result, "sub");
    
    if (server->mul(a, b, &result))
      return error_msg("mul");

    result_for(a, b, result, "mul");
    
    if (server->div(a, b, &result))
      return error_msg("div");

    result_for(a, b, result, "div");
  }

  return 0;
}

int error_msg(const char* str)
{
  printf("Error talking to server: %s\n", str); 
  return 1;
}

void result_for(l4_int32_t a, l4_int32_t b, l4_int32_t result, const char* str)
{
  printf("%d %s %d = %d\n", a, str, b, result);
}
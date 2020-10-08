#include <l4/re/util/cap_alloc>
#include <l4/sys/irq>
#include <l4/re/env>
#include <l4/sys/types.h>
#include <l4/re/error_helper>

#include <unistd.h>
#include <iostream>

int main()
{
  try
  {
    std::cout << "Server starting..\n";

    L4::Cap<L4::Irq> sender = L4Re::Env::env()->get_cap<L4::Irq>("irq");
    if (!sender.is_valid())
    {
      std::cerr << "Could not get cap irq\n";
      return 1;
    }

    for (;;)
    {
      L4Re::chksys(sender->trigger(), "Trigger error!\n");
      std::cout << "Trigger success\n";
      sleep(1);
    }
  }
  catch(L4::Runtime_error &e)
  {
    std::cerr << "Runtime error: " << e.str();
  }
  catch(...)
  {
    std::cerr << "Error occured!\n";
    return 1;
  }
  
  return 0;
}
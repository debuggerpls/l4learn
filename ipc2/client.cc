#include <l4/re/util/cap_alloc>
#include <l4/sys/irq>
#include <l4/re/env>
#include <l4/sys/types.h>
#include <l4/re/error_helper>

#include <pthread-l4.h>

#include <unistd.h>
#include <iostream>

int main()
{
  try
  {
    std::cout << "Client starting..\n";

    L4::Cap<L4::Irq> receiver = L4Re::Env::env()->get_cap<L4::Irq>("irq");
    if (!receiver.is_valid())
    {
      std::cerr << "Could not get cap irq\n";
      return 1;
    }

    L4Re::chksys(receiver->bind_thread(Pthread::L4::cap(pthread_self()), 0), "Could not bind to IRQ.");


    for (;;)
    {
      L4Re::chksys(receiver->receive(), "Receive error!\n");
      std::cout << "Received IRQ!\n";
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
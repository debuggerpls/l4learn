#include <l4/re/env>
#include <l4/re/error_helper>
#include <l4/re/util/cap_alloc>
#include <l4/sys/irq>
#include <l4/sys/factory>

#include <pthread-l4.h>
#include <thread>

#include <iostream>

int main()
{
  try
  {
    // initialize capability with invalid capability selector
    // chkcap() checks for valid capability or raises C++ exeption
    // allocate a capability to use for IRQ object   
    L4::Cap<L4::Irq> irq;
    irq = L4Re::chkcap(L4Re::Util::cap_alloc.alloc<L4::Irq>());

    // use default factory to create the IRQ object with the capability
    L4Re::chksys(L4Re::Env::env()->factory()->create(irq), "Failed to create IRQ.");

    // bind ourselves to the IRQ to receive its triggers
    L4Re::chksys(irq->bind_thread(Pthread::L4::cap(pthread_self()), 0), "Could not bind to IRQ.");

    // Create a thread and trigger the IRQ
    std::thread t = std::thread([irq](){ irq->trigger();});

    //Normally receiver is in blocked state, therefore should add Timeout to make it non-blocking
    //so you can comment out the thread to check for failed receive()
    //L4Re::chksys(irq->receive(L4_IPC_RECV_TIMEOUT_0), "Receive failed.");
    L4Re::chksys(irq->receive(), "Receive failed.");
    std::cout << "Received IRQ!\n";

    t.join();

    return 0;
  }
  catch(L4::Runtime_error &e)
  {
    std::cerr << "Runtime error: " << e.str();
  }
  catch(...)
  {
    std::cerr << "Unknown exception\n";
  }

  return 1;
}
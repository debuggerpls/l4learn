#include <l4/re/util/object_registry>
#include <l4/cxx/ipc_stream>
#include <l4/cxx/ipc_server>

#include <iostream>

using namespace L4;
using namespace L4Re;

struct SimpleServer : Server_object
{
  int dispatch(unsigned long, Ipc::Iostream &ios) override
  {
    int a, b;
    ios >> a >> b;
    std::cout << "Reveived: " << a << ", " << b << std::endl;
    ios << a * b;
    return L4_EOK;
  }
  Demand get_buffer_demand() const
  {
    return Demand(0);
  }
};

int main()
{
  SimpleServer simple_server;
  L4Re::Util::Registry_server<> server;
  Cap<void> cap = server.registry()->register_obj(&simple_server, "gate");
  if (!cap.is_valid())
  {
      std::cerr << "invalid cap on register_obj 'gate'" << std::endl;
      return 1;
  }
  server.loop();
  return 0;
}
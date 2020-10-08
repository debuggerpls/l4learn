#include <l4/re/util/cap_alloc>
#include <l4/re/env>
#include <l4/cxx/ipc_stream>
#include <l4/sys/utcb.h>
#include <l4/sys/types.h>

#include <iostream>


int main()
{
    std::cout << "Hello form client\n";

    L4::Cap<void> server = L4Re::Env::env()->get_cap<void>("gate");
    if (!server.is_valid())
    {
        std::cerr << "Could not get server capability!\n";
        return 1;
    }

    L4::Ipc::Iostream ios(l4_utcb());
    
    int a = 2;
    int b = 4;
    ios << a << b;

    l4_msgtag_t tag = ios.call(server.cap());
    if (l4_error(tag))
    {
        std::cerr << "calling server: " << l4_error(tag) << '\n';
        return 1;
    }

    int result;
    ios >> result;

    std::cout << "Sent: " << a << ", " << b << " , received: " << result << '\n';

    return 0;
}
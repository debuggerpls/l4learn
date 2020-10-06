#### Simple IPC using client/server example from L4Re

1. Declare interface (derived from L4::Kobject_t) 
   * See explanation in [Interface Definition Language][1]
   * declaration in *ipc_interface.h*
   * needed includes:
     * #include <l4/sys/capability> (Kobject)
     * #include <l4/sys/cxx/ipc_iface> (RPC macros)
  * Declare RPC functions and Rpcs typedef

2. Define server functions (derive from L4::Epiface_t)
   * [Epiface][4] - implementation for Kobject-based interface implementations.
   * WARNING: RPC params changes depending if you're server or client, check IDL page! Needs to prepend *op_* to each function!
   * Create server loop object [*server*][2] that has a [*Object_registry*][3] included.
     * Registry manages server objects and their IPC gates for a single server loop for a specific thread
   * [Register][5] a new server object to a pre-allocated receive endpoint (allocated in .cfg file)
   * [Check][6] if capability is a valid capability index
   * [Start][7] the server loop
   * includes:
     * #include <l4/sys/cxx/ipc_epiface>
     * #include <l4/re/util/br_manager>
     * #include <l4/re/util/object_registry>

3. Call RPCs from client to server:
   * Get *Calc* [capability][8] from [initial environment of the current task][9] by providing the *name* of cap defined in .cfg.
   * Check if capability is valid
   * Use *server* as pointer to the server object.

4. Create .cfg file for [NED][10]
   * Create new IPC Gate: *local gate = L4.default_loader:new_channel()*
   * Start *server* and *client* binaries
     * Set capability of server to *calc_server = gate:svr()* (Receiver, full access)
     * Set capability of client to *calc_server = gate* (Sender) 

5. Create modules.list with .cfg, server and client binaries

6. Create Makefile where you define names for client/server binaries
```
TARGET = ipc0_server ipc0_client
SRC_CC_ipc0_server = server.cc
SRC_CC_ipc0_client = client.cc
```

[1]: http://l4re.org/doc/l4_cxx_ipc_iface.html
[2]: http://l4re.org/doc/classL4Re_1_1Util_1_1Registry__server.html
[3]: http://l4re.org/doc/classL4Re_1_1Util_1_1Object__registry.html
[4]: http://l4re.org/doc/structL4_1_1Epiface__t.html
[5]: http://l4re.org/doc/classL4Re_1_1Util_1_1Object__registry.html#a8f518a9381dd3ea947d5adc5d0a614a0
[6]: http://l4re.org/doc/classL4_1_1Cap__base.html#ab4937bb12579c752564f7250760d0bda
[7]: http://l4re.org/doc/classL4Re_1_1Util_1_1Registry__server.html#a1f0c292e07be4f65600855b1cc40dc44
[8]: http://l4re.org/doc/classL4Re_1_1Env.html#a0e7a55ebbac0dedc9fa6859d32687d35
[9]: http://l4re.org/doc/classL4Re_1_1Env.html#acb46e812c2ee53b4bc849f680b8df9c8
[10]: http://l4re.org/doc/l4re_concepts_env_and_start.html
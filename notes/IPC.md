### Notes on IPC from [TUD][1]

* IPCs are synchronous in L4:
  * IPC partner blocks until other one gets ready
  * Direct copy between sender and receiver

* Can send:
  * Plain data
  * Resource mappings (flexpages)

* Types of IPC:
  * Send ( Sender -> Receiver )
  * Closed wait ( S <- R, Receive from )
  * Open wait ( ? <- R, Receive any )
  * Call ( send + receive from )
  * Reply & wait ( send + receive any )

* Timeouts can be non-blocking (0), with specific value(wait till partner ready or timeout), sleep is implemented as IPC to NIL(non-existing) thread with timeout

* IPC Gate is needed for IPC
  * Referenced through capability (local name)
  * Created using factory object
    * Each task is assigned factory object
    * Factory creates other objects
    * Can enforce quotas, perform accounting etc.
  * IPC Gate is bound to Receiver (Thread)
    * IPC channels are uni-directional
    * Anyone with gate capability can send, but only Receiver receives
  * Add a Label
    * A thread may receive from multiple gates
    * Label identifies where a message came from
  * Receiving:
    * Receiver calls Open Wait and waits for messages on any of its gates
    * Receive system call returns label of the used gate (not capability)
  * Replying:
    * Receiver doesnt have IPC Gate to sender
    * Kernel provides implicity reply capability (per-thread)
      * Valid until 1) reply send or 2) next wait started
  
* UTCB - User-level Thread Control Block
  * Set of "virtual" registers
    * Message registers
      * System call parameters
      * IPC: direct copy to receiver
    * Buffer registers
      * Receive flexpage descriptors
    * Thread Control Registers
      * Thread-private data
      * Preserved, not copied
  
  * Message Tag:
    * Protocol:
      * User-defined type of communication
      * Pre-defined system protocols (Page fault, IRQ etc)
    * Flags:
      * Special-purpose communication flags
    * Items:
      * Number of indirect items to copy
    * Words:
      * Number of direct items to copy

* L4Re uses Dedicated Kernel Objects for IPC
  * Invoke IPC on a kernel-object (IPC Gate) (which points to endpoint (capability))
  * Kernel object mapped to a virtual address (local name space)
    * Task only knows objects local name -> no information leaks through global names

* Finding service in L4Re
  * Need to get a capability mapped into my local capability space
    * Idea: translate human-readable-names into IDs -> need a name service provider

* Shared Memory
  * If applications need high throughput for lots of data -> sharing memory between tasks can provide better performance
  * Zero-copy communication
    * Producer writes data in place
    * Consumer reads data from same physical location
  * Kernel seldom involved
    * At setup: establish memory mapping
      * Flexpage IPC + resolution of pagefaults
    * Synchronization only when necessary
  * Example: Streaming media applications (FIFO queue)
    * Shared buffer betwenn consumer & producer
      * Wake up notification (IPC) when new data is ready
      * Wake up notification when free space for producer is available
      * Check possible pitfalls in Slides

* Asynchronous IPC (IRQ)
  * IRQ kernel object can be used for asynchronous communication

* L4 IPC calls are atomic


#### Further reading
* N. Feske: “A case study on the cost and benefit of dynamic RPC marshalling for low-level system components”
* Faehndrich, Aiken et al.: “Language support for fast and reliable message-based communication in Singularity OS”

[1]: https://os.inf.tu-dresden.de/Studium/KMB/WS2019/03-IPC.pdf
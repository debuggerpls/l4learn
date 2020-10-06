#### Example as in src/l4/pkg/examples/sys/uirq

Creating simple IRQ:
1. Initialize capability of L4::Irq
2. Allocate capability for the type L4::Irq
3. Create the object with capability using default factory
4. Bind the capability to ourselves to receive IRQ triggers
5. Create new thread that triggers the IRQ
6. Call receive on IRQ object in the main thread to receive the trigger
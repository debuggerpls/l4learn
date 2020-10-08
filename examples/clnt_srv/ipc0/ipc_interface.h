#include <l4/sys/capability>
#include <l4/sys/cxx/ipc_iface>

struct Calc : L4::Kobject_t<Calc, L4::Kobject>
{
  L4_INLINE_RPC(int, add, (l4_int32_t a, l4_int32_t b, l4_int32_t *result));
  L4_INLINE_RPC(int, sub, (l4_int32_t a, l4_int32_t b, l4_int32_t *result));
  L4_INLINE_RPC(int, mul, (l4_int32_t a, l4_int32_t b, l4_int32_t *result));
  L4_INLINE_RPC(int, div, (l4_int32_t a, l4_int32_t b, l4_int32_t *result));

  typedef L4::Typeid::Rpcs<add_t, sub_t, mul_t, div_t> Rpcs;
};
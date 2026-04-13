#include "hal.h"

static loongarch64_trap_handler_t g_handlers[LOONGARCH64_MAX_TRAPS];
static UINT64 g_dispatch_counts[LOONGARCH64_MAX_TRAPS];
static UINT64 g_unhandled_count;

void loongarch64_trap_init(void)
{
  UINTN i;
  for (i = 0; i < LOONGARCH64_MAX_TRAPS; ++i)
  {
    g_handlers[i] = 0;
    g_dispatch_counts[i] = 0;
  }
  g_unhandled_count = 0;
}

int loongarch64_trap_register(UINTN vector, loongarch64_trap_handler_t handler)
{
  if (vector >= LOONGARCH64_MAX_TRAPS)
    return -1;

  g_handlers[vector] = handler;
  return 0;
}

void loongarch64_trap_dispatch(UINTN vector, const loongarch64_trap_context *ctx)
{
  if (vector >= LOONGARCH64_MAX_TRAPS)
  {
    ++g_unhandled_count;
    return;
  }

  ++g_dispatch_counts[vector];
  if (g_handlers[vector] != 0)
  {
    g_handlers[vector](ctx);
    return;
  }

  ++g_unhandled_count;
}

UINT64 loongarch64_trap_dispatch_count(UINTN vector)
{
  if (vector >= LOONGARCH64_MAX_TRAPS)
    return 0;
  return g_dispatch_counts[vector];
}

UINT64 loongarch64_trap_unhandled_count(void)
{
  return g_unhandled_count;
}

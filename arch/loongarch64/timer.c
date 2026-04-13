#include "hal.h"

static UINT64 g_tick_hz;
static UINT64 g_ticks;

void loongarch64_timer_init(UINT64 tick_hz)
{
  if (tick_hz == 0)
    tick_hz = 100;
  g_tick_hz = tick_hz;
  g_ticks = 0;
}

void loongarch64_timer_tick(void)
{
  ++g_ticks;
}

UINT64 loongarch64_timer_ticks(void)
{
  return g_ticks;
}

UINT64 loongarch64_timer_hz(void)
{
  return g_tick_hz;
}

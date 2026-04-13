#ifndef FREEDOS_LOONGARCH64_HAL_H
#define FREEDOS_LOONGARCH64_HAL_H

#include "uefi.h"

#define LOONGARCH64_MAX_TRAPS 256

typedef struct
{
  UINTN vector;
  UINT64 cause;
  UINT64 epc;
  UINT64 badv;
} loongarch64_trap_context;

typedef void (*loongarch64_trap_handler_t)(const loongarch64_trap_context *ctx);

void loongarch64_trap_init(void);
int loongarch64_trap_register(UINTN vector, loongarch64_trap_handler_t handler);
void loongarch64_trap_dispatch(UINTN vector, const loongarch64_trap_context *ctx);
UINT64 loongarch64_trap_dispatch_count(UINTN vector);
UINT64 loongarch64_trap_unhandled_count(void);

void loongarch64_timer_init(UINT64 tick_hz);
void loongarch64_timer_tick(void);
UINT64 loongarch64_timer_ticks(void);
UINT64 loongarch64_timer_hz(void);

void loongarch64_memory_init(const EFI_MEMORY_DESCRIPTOR *memory_map, UINTN map_size, UINTN descriptor_size);
void *loongarch64_memory_alloc(UINTN size, UINTN alignment);
UINT64 loongarch64_memory_total_pages(void);
UINT64 loongarch64_memory_available_pages(void);

#endif

#include "hal.h"

#define LOONGARCH64_EARLY_HEAP_SIZE (128 * 1024)
#define EFI_CONVENTIONAL_MEMORY 7U

static UINT8 g_early_heap[LOONGARCH64_EARLY_HEAP_SIZE];
static UINTN g_early_heap_offset;

static UINT64 g_total_pages;
static UINT64 g_available_pages;

static UINTN align_up(UINTN value, UINTN alignment)
{
  if (alignment == 0)
    alignment = 1;
  return (value + alignment - 1) & ~(alignment - 1);
}

void loongarch64_memory_init(const EFI_MEMORY_DESCRIPTOR *memory_map, UINTN map_size, UINTN descriptor_size)
{
  const UINT8 *cursor = (const UINT8 *)memory_map;
  UINTN offset = 0;

  g_early_heap_offset = 0;
  g_total_pages = 0;
  g_available_pages = 0;

  if (memory_map == 0 || descriptor_size == 0)
    return;

  while (offset + descriptor_size <= map_size)
  {
    const EFI_MEMORY_DESCRIPTOR *desc = (const EFI_MEMORY_DESCRIPTOR *)(cursor + offset);
    g_total_pages += desc->NumberOfPages;
    if (desc->Type == EFI_CONVENTIONAL_MEMORY)
      g_available_pages += desc->NumberOfPages;
    offset += descriptor_size;
  }
}

void *loongarch64_memory_alloc(UINTN size, UINTN alignment)
{
  UINTN start = align_up(g_early_heap_offset, alignment);
  UINTN end = start + size;

  if (size == 0)
    return 0;

  if (end < start || end > LOONGARCH64_EARLY_HEAP_SIZE)
    return 0;

  g_early_heap_offset = end;
  return &g_early_heap[start];
}

UINT64 loongarch64_memory_total_pages(void)
{
  return g_total_pages;
}

UINT64 loongarch64_memory_available_pages(void)
{
  return g_available_pages;
}

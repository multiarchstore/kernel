#include "uefi.h"
#include "hal.h"

static void loongarch64_dummy_trap_handler(const loongarch64_trap_context *ctx)
{
  (void)ctx;
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
  static CHAR16 msg[] = {
      'F', 'r', 'e', 'e', 'D', 'O', 'S', ' ', 'L', 'o', 'o', 'n', 'g', 'A', 'r', 'c', 'h', '6', '4', ' ', 'U', 'E', 'F', 'I', ' ', 'M', 'i', 'l', 'e', 's', 't', 'o', 'n', 'e', ' ', '2', '\r', '\n', 0};
  static CHAR16 ready[] = {
      'M', '2', ':', ' ', 't', 'r', 'a', 'p', '/', 't', 'i', 'm', 'e', 'r', '/', 'm', 'e', 'm', ' ', 'h', 'o', 'o', 'k', 's', ' ', 'r', 'e', 'a', 'd', 'y', '\r', '\n', 0};
  loongarch64_trap_context test_ctx;

  (void)ImageHandle;
  loongarch64_trap_init();
  loongarch64_timer_init(1000);
  loongarch64_memory_init(0, 0, 0);
  loongarch64_trap_register(0, loongarch64_dummy_trap_handler);

  test_ctx.vector = 0;
  test_ctx.cause = 0;
  test_ctx.epc = 0;
  test_ctx.badv = 0;
  loongarch64_trap_dispatch(0, &test_ctx);
  loongarch64_timer_tick();
  (void)loongarch64_memory_alloc(64, 16);

  if (SystemTable != 0 && SystemTable->ConOut != 0 && SystemTable->ConOut->OutputString != 0)
  {
    EFI_STATUS status = SystemTable->ConOut->OutputString(SystemTable->ConOut, msg);
    if (status != EFI_SUCCESS)
      return status;
    return SystemTable->ConOut->OutputString(SystemTable->ConOut, ready);
  }

  return EFI_SUCCESS;
}

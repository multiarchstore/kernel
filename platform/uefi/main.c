#include "uefi.h"

void loongarch64_timer_init(void);
void loongarch64_trap_init(void);

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
  static CHAR16 msg[] = {
      'F', 'r', 'e', 'e', 'D', 'O', 'S', ' ', 'L', 'o', 'o', 'n', 'g', 'A', 'r', 'c', 'h', '6', '4', ' ', 'U', 'E', 'F', 'I', ' ', 'M', 'i', 'l', 'e', 's', 't', 'o', 'n', 'e', ' ', '1', '\r', '\n', 0};

  (void)ImageHandle;
  loongarch64_trap_init();
  loongarch64_timer_init();

  if (SystemTable != 0 && SystemTable->ConOut != 0 && SystemTable->ConOut->OutputString != 0)
    return SystemTable->ConOut->OutputString(SystemTable->ConOut, msg);

  return EFI_SUCCESS;
}

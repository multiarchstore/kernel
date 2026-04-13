OUTPUT_FORMAT("elf64-loongarch")
OUTPUT_ARCH(loongarch)
ENTRY(efi_main)

SECTIONS
{
  . = 0;

  .text : {
    *(.text*)
  }

  .rodata : {
    *(.rodata*)
  }

  .data : {
    *(.data*)
  }

  .bss : {
    *(.bss*)
    *(COMMON)
  }
}

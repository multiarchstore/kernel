# FreeDOS LoongArch64 UEFI (Milestone 2)

This repository is historically a 16-bit/32-bit x86 DOS kernel.
The LoongArch64 + UEFI work is introduced incrementally.

## Scope in this milestone

- Keeps `arch/loongarch64` startup/trap/timer entry scaffolding.
- Adds a basic LoongArch64 HAL interface in `arch/loongarch64/hal.h`.
- Adds trap subsystem primitives:
  - handler registration
  - trap dispatch function
  - per-vector/unhandled counters
- Adds timer subsystem primitives:
  - tick frequency configuration
  - software tick counter
- Adds early memory hooks:
  - UEFI memory map page accounting
  - fixed-size bump allocator for early allocations
- Updates UEFI entry flow to initialize trap/timer/memory subsystems and print Milestone 2 status.

This milestone still does **not** provide DOS compatibility on LoongArch64.

## Toolchain

The build target uses `loongarch64-unknown-linux-gnu-*` tools from:

- https://github.com/loong64/cross-tools

Install toolchain binaries and make sure they are on `PATH`, or set `CROSS_COMPILE`.

## Build

```bash
make loongarch64_uefi
```

Optional custom prefix:

```bash
make loongarch64_uefi CROSS_COMPILE=/opt/x-tools/loongarch64-unknown-linux-gnu/bin/loongarch64-unknown-linux-gnu-
```

Artifacts are written to:

- `_output/loongarch64_uefi/freedos-loongarch64.elf`
- `_output/loongarch64_uefi/BOOTLOONGARCH64.EFI`

## Next milestones

- Milestone 3: UEFI Block I/O integration and FAT/config load.
- Milestone 4: DOS API core adaptation behind architecture/platform HAL.
- Milestone 5: compatibility and regression validation.

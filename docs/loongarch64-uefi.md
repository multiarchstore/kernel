# FreeDOS LoongArch64 UEFI (Milestone 1)

This repository is historically a 16-bit/32-bit x86 DOS kernel.
The LoongArch64 + UEFI work is introduced incrementally.

## Scope in this milestone

- Adds `arch/loongarch64` scaffold files for startup/trap/timer entry points.
- Adds `platform/uefi` scaffold with minimal UEFI type definitions.
- Adds a standalone LoongArch64 UEFI target that builds a simple EFI app printing a boot banner.

This milestone does **not** yet provide DOS compatibility on LoongArch64.

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

- Milestone 2: memory manager hooks, timer, and trap/exception handling.
- Milestone 3: UEFI Block I/O integration and FAT/config load.
- Milestone 4: DOS API core adaptation behind architecture/platform HAL.
- Milestone 5: compatibility and regression validation.

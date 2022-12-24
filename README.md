#  UnknownRebuilder
[![CMake-windows-latest](https://github.com/NewWorldComingSoon/UnknownRebuilder/actions/workflows/CMake-windows-latest.yml/badge.svg)](https://github.com/NewWorldComingSoon/UnknownRebuilder/actions/workflows/CMake-windows-latest.yml)
[![GitHub license](https://img.shields.io/github/license/NewWorldComingSoon/UnknownRebuilder
)](https://github.com/NewWorldComingSoon/UnknownRebuilder/blob/main/LICENSE)

X86 native code rebuilder using UnknownIR(UIR) and UnknownMC(UMC).

```mermaid
flowchart LR
A1[Frontend-X86] -->B(UIR)
A2[Frontend-ARM] -->B(UIR)
B -->C(UIR Pass)
C -->D(UMC)
D -->E(UMC Pass)
E -->F1[Backend-X86]
E -->F2[Backend-ARM]
```

## What's UIR?
Yet another Intermediate Representation(IR) called UnknownIR(UIR).

## What's UMC?
Yet another Machine Code(MC) called UnknownMC(UMC).

## Motivation
Just for learning. Maybe it can help others too.

## Credit
- [cmkr](https://github.com/build-cpp/cmkr)
- [LLVM](https://github.com/llvm/llvm-project)
- [RetDec](https://github.com/avast/retdec)
- [VTIL](https://github.com/vtil-project)
- [Capstone](https://github.com/NewWorldComingSoon/capstone-retdec) 
- [Keystone](https://github.com/NewWorldComingSoon/keystone-retdec)
- [RawPDB](https://github.com/NewWorldComingSoon/raw_pdb)

## Build
Only tested on Windows, other systems have not been tested.
```
cmake -Bbuild -DCAPSTONE_BUILD_TESTS=OFF -DCAPSTONE_BUILD_SHARED=OFF -DCAPSTONE_BUILD_STATIC_RUNTIME=ON -DLLVM_TARGETS_TO_BUILD=X86
```

## Note
This is currently an unfinished project.

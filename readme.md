Setup the Tianocore code for build
Go into Conf -> target.txt
```
#
#  Copyright (c) 2006 - 2019, Intel Corporation. All rights reserved.<BR>
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
#
#  ALL Paths are Relative to WORKSPACE

#  Separate multiple LIST entries with a SINGLE SPACE character, do not use comma characters.
#  Un-set an option by either commenting out the line, or not setting a value.

ACTIVE_PLATFORM       = UefiLessonsPkg/UefiLessonsPkg.dsc
TARGET                = RELEASE
TARGET_ARCH           = X64
TOOL_CHAIN_CONF       = Conf/tools_def.txt
TOOL_CHAIN_TAG        = GCC5
BUILD_RULE_CONF = Conf/build_rule.txt
```



to build the Tianocore code 
. ./edksetup.sh && build


To run the qemu instance 
sudo qemu-system-x86_64 -drive if=pflash,format=raw,file=Build/OvmfX64/RELEASE_GCC5/FV/OVMF.fd -drive format=raw,file=fat:rw:~/UEFI_disk -nographic -net none -enable-kvm

where UEFI_disk is folder which contains all the binary output of our package
use -s if using with gdb
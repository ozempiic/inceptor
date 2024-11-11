#ifndef SYSCALL_H
#define SYSCALL_H

#include <ntddk.h>

NTSTATUS RestoreOriginalInstruction(PVOID originalSyscall);

#endif // SYSCALL_H

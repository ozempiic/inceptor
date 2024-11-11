#ifndef HOOK_H
#define HOOK_H

#include <ntddk.h>

// Forward declaration of InjectJumpInstruction from assembler.h
NTSTATUS InjectJumpInstruction(PVOID targetAddress, PVOID hookFunction);

// Declare the hooking function
NTSTATUS HookKeQuerySystemTime();

// Declare the hooked function
VOID HookedFunction(PLARGE_INTEGER SystemTime);

#endif // HOOK_H

#ifndef RESOLVE_H
#define RESOLVE_H

#include <ntddk.h>

// Function to resolve the address of a kernel function by its name
PVOID ResolveKernelFunctionAddress(UNICODE_STRING functionName);

// Function to check if a resolved function address is valid
BOOLEAN IsAddressValid(PVOID address);

#endif // RESOLVE_H

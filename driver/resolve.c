#include <ntddk.h>
#include "resolve.h"

PVOID ResolveKernelFunctionAddress(UNICODE_STRING functionName) {
    PVOID functionAddress;

    functionAddress = MmGetSystemRoutineAddress(&functionName);

    if (functionAddress == NULL) {
        DbgPrint("Failed to resolve address for %wZ\n", &functionName);
    }
    else {
        DbgPrint("Resolved address for %wZ: %p\n", &functionName, functionAddress);
    }

    return functionAddress;
}

BOOLEAN IsAddressValid(PVOID address) {
    if (address == NULL) {
        return FALSE;
    }

    return TRUE;
}

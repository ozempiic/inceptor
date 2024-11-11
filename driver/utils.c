#include <ntddk.h>
#include "utils.h"

NTSTATUS NTAPI ZwProtectVirtualMemory(
    HANDLE ProcessHandle,
    PVOID* BaseAddress,
    PSIZE_T RegionSize,  
    ULONG NewProtect,
    PULONG OldProtect
);

NTSTATUS ChangeMemoryProtection(PVOID address, SIZE_T size, ULONG protection) {
    ULONG oldProtection;
    PSIZE_T sizePtr = &size;  
    NTSTATUS status = ZwProtectVirtualMemory(NtCurrentProcess(), &address, sizePtr, protection, &oldProtection);
    return status;
}

VOID LogDebugMessage(const char* message) {
    DbgPrint("%s", message);
}

PVOID AllocateNonPagedMemory(SIZE_T size) {
    PVOID allocatedMemory = ExAllocatePoolWithTag(NonPagedPool, size, 'tag1');
    if (!allocatedMemory) {
        DbgPrint("Memory allocation failed\n");
    }
    return allocatedMemory;
}

VOID FreeNonPagedMemory(PVOID address) {
    if (address) {
        ExFreePoolWithTag(address, 'tag1');
    }
}

NTSTATUS CopyMemory(PVOID destination, PVOID source, SIZE_T size) {
    if (destination == NULL || source == NULL) {
        return STATUS_INVALID_PARAMETER;
    }
    RtlCopyMemory(destination, source, size);
    return STATUS_SUCCESS;
}

const char* GetLastErrorString(NTSTATUS status) {
    switch (status) {
    case STATUS_SUCCESS:
        return "Success";
    case STATUS_ACCESS_DENIED:
        return "Access Denied";
    case STATUS_INVALID_PARAMETER:
        return "Invalid Parameter";
    case STATUS_INSUFFICIENT_RESOURCES:
        return "Insufficient Resources";
    case STATUS_UNSUCCESSFUL:
        return "Unsuccessful";
    default:
        return "Unknown Error";
    }
}

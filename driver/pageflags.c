#include <ntddk.h>
#include "pageflags.h"

NTSTATUS ZwProtectVirtualMemory(
    HANDLE ProcessHandle,
    PVOID* BaseAddress,
    PSIZE_T RegionSize,
    ULONG NewProtect,
    PULONG OldProtect
);

NTSTATUS ChangeMemoryProtections(PVOID BaseAddress, SIZE_T Size, ULONG NewProtection) {
    NTSTATUS status;
    ULONG oldProtection;

    HANDLE currentProcess = PsGetCurrentProcessId();

    status = ZwProtectVirtualMemory(currentProcess, &BaseAddress, &Size, NewProtection, &oldProtection);

    if (!NT_SUCCESS(status)) {
        DbgPrint("Failed to change memory protection: 0x%08x\n", status);
        return status;
    }

    DbgPrint("Memory protection changed successfully.\n");
    return STATUS_SUCCESS;
}

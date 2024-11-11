#include <ntddk.h>
#include "syscall.h"
#include "resolve.h"  
#include "assembler.h" 

NTSTATUS ZwProtectVirtualMemory(
    HANDLE ProcessHandle,
    PVOID* BaseAddress,
    PSIZE_T RegionSize,
    ULONG NewProtect,
    PULONG OldProtect
);

NTSTATUS RestoreOriginalInstruction(PVOID originalSyscall) {
    ULONG oldProtect;
    SIZE_T regionSize = sizeof(UCHAR) * 5;  
    UCHAR originalInstruction[5];           

    HANDLE currentProcess = PsGetCurrentProcessId();

    NTSTATUS status = ZwProtectVirtualMemory(currentProcess, &originalSyscall, &regionSize, PAGE_EXECUTE_READWRITE, &oldProtect);
    if (!NT_SUCCESS(status)) {
        DbgPrint("Failed to change memory protection\n");
        return status;
    }

    RtlCopyMemory(originalInstruction, originalSyscall, sizeof(originalInstruction));

    RtlCopyMemory(originalSyscall, originalInstruction, sizeof(originalInstruction));

    status = ZwProtectVirtualMemory(currentProcess, &originalSyscall, &regionSize, oldProtect, &oldProtect);
    if (!NT_SUCCESS(status)) {
        DbgPrint("Failed to restore memory protection\n");
        return status;
    }

    DbgPrint("Successfully restored the original instruction\n");
    return STATUS_SUCCESS;
}

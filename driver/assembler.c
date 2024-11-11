#include <ntddk.h>

NTSTATUS ZwProtectVirtualMemory(
    HANDLE ProcessHandle,
    PVOID* BaseAddress,
    PULONG NumberOfBytesToProtect,
    ULONG NewAccessProtection,
    PULONG OldAccessProtection
);

NTSTATUS InjectJumpInstruction(PVOID targetAddress, PVOID hookFunction) {
    ULONG oldProtect;
    ULONG regionSize = 5;

    ULONG_PTR target = (ULONG_PTR)targetAddress;
    ULONG_PTR hook = (ULONG_PTR)hookFunction;
    ULONG_PTR jumpOffset = hook - target - 5;

    HANDLE currentProcess = PsGetCurrentProcessId();

    NTSTATUS status = ZwProtectVirtualMemory(
        currentProcess,               
        &targetAddress,               
        &regionSize,                  
        PAGE_EXECUTE_READWRITE,       
        &oldProtect                   
    );

    if (!NT_SUCCESS(status)) {
        DbgPrint("Failed to change memory protection\n");
        return status;
    }

    UCHAR jumpInstruction[5];
    jumpInstruction[0] = 0xE9;  
    *((ULONG*)&jumpInstruction[1]) = (ULONG)jumpOffset;

    RtlCopyMemory(targetAddress, jumpInstruction, sizeof(jumpInstruction));

    status = ZwProtectVirtualMemory(
        currentProcess,               
        &targetAddress,               
        &regionSize,                  
        oldProtect,                   
        &oldProtect                   
    );

    if (!NT_SUCCESS(status)) {
        DbgPrint("Failed to restore memory protection\n");
        return status;
    }

    DbgPrint("Jump instruction injected successfully\n");
    return STATUS_SUCCESS;
}

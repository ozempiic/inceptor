#include <ntddk.h>
#include "hook.h"
#include "resolve.h"
#include "utils.h"
#include "assembler.h" 

typedef VOID(*KeQuerySystemTime_t)(PLARGE_INTEGER SystemTime);

KeQuerySystemTime_t OriginalKeQuerySystemTime = NULL;

VOID HookedFunction(PLARGE_INTEGER SystemTime) {
    DbgPrint("Hooked KeQuerySystemTime!\n");
    if (OriginalKeQuerySystemTime) {
        OriginalKeQuerySystemTime(SystemTime);  
    }
}

NTSTATUS HookKeQuerySystemTime() {
    UNICODE_STRING FunctionName;
    PVOID FunctionAddress;

    RtlInitUnicodeString(&FunctionName, L"KeQuerySystemTime");
    FunctionAddress = ResolveKernelFunctionAddress(FunctionName);
    if (!FunctionAddress) {
        return STATUS_UNSUCCESSFUL;
    }

    OriginalKeQuerySystemTime = (KeQuerySystemTime_t)FunctionAddress;

    NTSTATUS status = InjectJumpInstruction(FunctionAddress, (PVOID)HookedFunction);
    if (!NT_SUCCESS(status)) {
        DbgPrint("Failed to inject jump into KeQuerySystemTime\n");
        return status;
    }

    DbgPrint("Successfully hooked KeQuerySystemTime\n");
    return STATUS_SUCCESS;
}

NTSTATUS UnhookKeQuerySystemTime() {
    if (OriginalKeQuerySystemTime != NULL) {
        NTSTATUS status = InjectJumpInstruction((PVOID)OriginalKeQuerySystemTime, (PVOID)OriginalKeQuerySystemTime);
        if (!NT_SUCCESS(status)) {
            DbgPrint("Failed to unhook KeQuerySystemTime\n");
            return status;
        }
        DbgPrint("Successfully unhooked KeQuerySystemTime\n");
    }
    return STATUS_SUCCESS;
}

#include <ntddk.h>
#include "driver.h"
#include "hook.h"
#include "utils.h"

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);
    DbgPrint("Driver loaded\n");

    if (DriverObject == NULL) {
        DbgPrint("DriverObject is NULL\n");
        return STATUS_UNSUCCESSFUL;
    }

    NTSTATUS status = STATUS_SUCCESS; 

    // status = HookKeQuerySystemTime();
    if (!NT_SUCCESS(status)) {
        DbgPrint("Failed to hook KeQuerySystemTime with status: 0x%x\n", status);
        return status;
    }

    DbgPrint("Driver entry completed successfully.\n");

    DriverObject->DriverUnload = DriverUnload;

    return STATUS_SUCCESS;
}

VOID DriverUnload(PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
    DbgPrint("Driver unloaded\n");
}

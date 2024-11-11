#ifndef DRIVER_H
#define DRIVER_H

#include <ntddk.h>

// Declare the driver entry point, which is called when the driver is loaded
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath);

// Declare the driver unload function, which is called when the driver is unloaded
VOID DriverUnload(PDRIVER_OBJECT DriverObject);

#endif // DRIVER_H

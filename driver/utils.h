#ifndef UTILS_H
#define UTILS_H

#include <ntddk.h>

extern NTSTATUS ChangeMemoryProtection(PVOID address, SIZE_T size, ULONG protection);

#endif // UTILS_H

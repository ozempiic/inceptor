#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <ntddk.h>

// Inject a jump (JMP) instruction into the target address
// This modifies the function at targetAddress to redirect to hookFunction
NTSTATUS InjectJumpInstruction(PVOID targetAddress, PVOID hookFunction);

#endif // ASSEMBLER_H

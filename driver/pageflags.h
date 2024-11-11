#ifndef PAGEFLAGS_H
#define PAGEFLAGS_H

// Memory protection flags
#define PAGE_EXECUTE_READWRITE 0x40      // Allows both execution and read/write
#define PAGE_READWRITE 0x04             // Allows read and write access
#define PAGE_EXECUTE 0x10              // Allows execution
#define PAGE_READONLY 0x02             // Allows read-only access

#endif // PAGEFLAGS_H

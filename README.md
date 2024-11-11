
# Inceptor

A kernel-mode driver for Windows designed to intercept and modify syscalls by dynamically hooking functions. It injects jump instructions to redirect kernel functions, allowing real-time monitoring, logging, and control over system behavior.


## Features
- Dynamic hooking of Windows kernel functions
- Injects custom jump instructions for function redirection
- Modifies and restores memory protection levels
- Logs and monitors hooked function calls
- Supports easy function unhooking for safe unloading
- Resolves and validates kernel function addresses dynamically


## Dependencies
- [Windows Driver Kit (WDK)](https://learn.microsoft.com/en-us/windows-hardware/drivers/download-the-wdk)
- [Visual Studio](https://visualstudio.microsoft.com/downloads/)
- Windows-compatible debugging tools (WinDbg)
## Setup

1. Clone the repository to your local machine.
2. Install the Windows Driver Kit (WDK) for driver development.
3. Open the project in Visual Studio.
4. Build the driver in Release mode to create the `.sys` file.
5. Ensure kernel debugging is enabled on your target machine.
6. Load the driver onto the system

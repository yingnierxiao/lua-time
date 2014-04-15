ul_time
=======
  
Timing functions for Lua "os" module.
Compilation with gcc (Linux) or MinGW-gcc (Windows).

Cross-compilation in Linux:
* 32-bit target: `make COMSPEC=command`  
* 64-bit target: `make COMSPEC=command PROCESSOR_ARCHITECTURE=AMD64 CPU=k8`
  
Module functions:
* `os.delay_us(n)` (delay for n microseconds)
* `os.delay_ms(n)` (delay for n milliseconds)
* `os.sec_usec()` (returns 2 numbers - current absolute seconds and microseconds as returned by gettimeofday function).

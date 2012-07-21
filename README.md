# Windows Resolution Timer API
A basic example that demonstrates the undocumented/hidden windows resolution timer API in win32.

### How it works
The example queries for the system for the maximum possible resolution and sets the internal timer to that resolution.

### About
I just wanted to release this, as I have seen some people trying to sell applications that manipulate the internal windows timer. Which I find ridiculous :).
Personally I do not recommend manipulating the internal timer for performance reasons; using the maximum frequency, resulted in a preposterous [DPC Latency](http://en.wikipedia.org/wiki/Deferred_Procedure_Call "Deferred Procedure Call").

### Tested
Tested on Windows 7/XP using the MSVC++ compiler.
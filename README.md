# Simple C log library

The purpose of this library is to provide a simple meaningful output
without too many unused features. This is an evolving library so it is expected to
add more features in the future but this will always remain the core of the library.

## APIs

The library offers minimal API to get you started. See example below.
```c
#include "log_t/log.h"

int main(void)
{
    log_t_init();
    log_info("Hello World\n");
    log_t_deinit();

    return 0;
}
```
Calling `log_t_init()` and `log_t_deinit()` is a **must** and the user of the library must call it
at least once. It is ok to spam `log_t_init()` where the user pleases but be advised it may not
be a good practice. The recommendation is to only call it once for example in your main function.

| API                   | Description       | Use case |
| --------------------- | ----------------- | -------- |
| log_t_init()          | initial log library | once everytime you want to use the library |
| log_t_deinit()        | deinitial log library | once after you're done using the library |
| log_t_set_level()     | change log level from default of info level | use when you want to add or remove more logging |
| log_trace()           | lowest level of log (value of 0) | use when needed to follow important logic |
| log_debug()           | level of log value of 1 | use for debugging statement (e.g. debug build) |
| log_info()            | level of log value of 2 | used for wanted info (but not needed) |
| log_warning()         | level of log value of 3 | used to warn but it won't break the code (something fishy) |
| log_error()           | level of log value of 4 | used for error that can't be ignored |
| log_fatal()           | level of log value of 5 | used for fatality level of code its mayhem if this log is used |


## Log Level Explained

As noticed by the API table above, there are 6 total log level each having their use case. The use cases
are not set in stone and the user can define their own cases of the respective given log. By
default log level is set to that of **info**. This means *info, warning, error, and fatal* will be logged but no logging of 
*trace and debug* will be logged even if they are used. Only by using `log_t_set_level()` and
passing the correct log value can the respective log and everything above will be shown. For example,
to see **debug** log along with the rest but not including *trace* we can set the log level to
`log_t_set_level(LOG_L_DEBUG);` (note the rest of the log enum values are within the header file of 
log_t/log.h). 

The user may have to use a macro mechanism during their builds to enable different level of logging
or programmatically do it. Below a macro mechanism example.
```c
#include "log_t/log.h"

int main(void)
{
    log_t_init();
#ifdef DEBUG
    log_t_set_level(LOG_L_DEBUG);
#endif
    log_info("Hello World\n");
    log_debug("Goodbye Cruel World\n");

    return 0;
}
```
Regular compilation may look like the following assuming the given example is saved in a file called
*main.c* and we are in the same directory as the file. Then we can do
```bash
gcc -DDEBUG main.c -o main
./main
```
To see *Goodbye Cruel World* output or just do
```bash
gcc main.c -o main
./main
```
Which will only show *Hello World* output. **In both compilations *Hello World* will be outputted**

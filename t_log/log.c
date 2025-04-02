#include "log.h"
#include <bits/time.h>
#include <string.h>
#include <stdlib.h>

/* can only be one have one global instance
 * need to call log_t_init() at least once!
 */
static struct t_log *inst = NULL; 

static const char* log_l_str[LOG_L_TOTAL] = {
    "\e[1;36mTRACE\e[0m",
    "\e[1;35mDEBUG\e[0m",
    "\e[1;33mINFO \e[0m",
    "\e[0mWARN ",
    "\e[1;31mERROR\e[0m",
    "\e[4;31mFATAL\e[0m"
};

static inline const char *get_log_l_str(enum log_level l)
{
    return log_l_str[l];
}

void log_t_init(void)
{
    if (inst != NULL)
        return;

    inst = (struct t_log *)malloc(sizeof(struct t_log));
    memset(inst, 0, sizeof(*inst));
    clock_gettime(CLOCK_MONOTONIC, &inst->start_time);
}

void __t_log(enum log_level l, const char *fname, int line, const char *fn_name,
        const char *msg_fmt, ...)
{
    va_list args;
    va_start(args, msg_fmt);
    FILE *stream = NULL;
    double elapsed_time = 0;
    struct timespec current_time;

    clock_gettime(CLOCK_MONOTONIC, &current_time);
    /* microsecond precision */
    elapsed_time = (current_time.tv_sec - inst->start_time.tv_sec) +
                   (current_time.tv_nsec - inst->start_time.tv_nsec) / 1e6;
    
    switch(l) {
    case LOG_L_INFO:
        stream = stdout;
        break;
    case LOG_L_TRACE:
    case LOG_L_DEBUG:
    case LOG_L_WARNING:
    case LOG_L_ERROR:
    case LOG_L_FATAL:
        stream = stderr;
    }

    fprintf(stream, "%s \e[1;32m[%12.6f]\e[0m \e[1;34m<%s:%d %s()>\e[0m: ", get_log_l_str(l),
            elapsed_time , fname, line, fn_name);
    vfprintf(stream, msg_fmt, args);
    va_end(args);
}

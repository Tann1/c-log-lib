#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

enum log_level {
    LOG_L_TRACE,
    LOG_L_DEBUG,
    LOG_L_INFO,
    LOG_L_WARNING,
    LOG_L_ERROR,
    LOG_L_FATAL,
    LOG_L_TOTAL
};

struct t_log {
    int tmp;
    struct timespec start_time;
};


void log_t_init(void);

/* log output format
 * <log level>(def,opt) [<time>(def,opt)] <filename><def,opt> -- <function>(def,opt).<linenumber>(def, opt): <message>(req)
 * example of debug:
 * debug [      0.123] foo.c -- bar.123: hello world!
 */

void __t_log(enum log_level l, const char *fname, int line, const char *fn_name,
        const char *msg_fmt, ...);

#define log_trace(msg, ...) \
    __t_log(LOG_L_TRACE, __FILE__, __LINE__, __FUNCTION__, \
            msg, ##__VA_ARGS__)
#define log_debug(msg, ...) \
    __t_log(LOG_L_DEBUG, __FILE__, __LINE__, __FUNCTION__, \
            msg, ##__VA_ARGS__)
#define log_info(msg, ...) \
    __t_log(LOG_L_INFO, __FILE__, __LINE__, __FUNCTION__, \
            msg, ##__VA_ARGS__)
#define log_warning(msg, ...) \
    __t_log(LOG_L_WARNING, __FILE__, __LINE__, __FUNCTION__, \
            msg, ##__VA_ARGS__)
#define log_error(msg, ...) \
    __t_log(LOG_L_ERROR, __FILE__, __LINE__, __FUNCTION__, \
            msg, ##__VA_ARGS__)
#define log_fatal(msg, ...) \
    __t_log(LOG_L_FATAL, __FILE__, __LINE__, __FUNCTION__, \
            msg, ##__VA_ARGS__)
#ifdef __cplusplus
}
#endif
#endif

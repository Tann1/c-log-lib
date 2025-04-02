#include "t_log/log.h"

int main(void)
{
    log_t_init();

    log_trace("hello world\n");
    log_info("hello world\n");
    log_debug("hello world\n");
    log_warning("hello world\n");
    log_error("hello world\n");
    log_fatal("hello world\n");

    log_t_set_level(LOG_L_TRACE);
    log_trace("hello world\n");
    log_info("hello world\n");
    log_debug("hello world\n");
    log_warning("hello world\n");
    log_error("hello world\n");
    log_fatal("hello world\n");

    return 0;
}

#include <stdio.h>
#include <time.h>

typedef void (*logging_func)();

#define DEBUG 0
#define INFO 1
#define WARN 2
#define ERR 3
#define CRIT 4
#define MAX (CRIT+1)

void null_logger()
{
    // do-nothing function
}

int logger_mask = 0;
logging_func app_loggers[MAX] = {null_logger, null_logger, null_logger, null_logger, null_logger};

typedef struct log_time_measure
{
    struct timespec start;
    struct timespec end;
} log_time_measure;

log_time_measure time_store[2];

int main()
{
    int iteration = 10000;

    clock_gettime(CLOCK_MONOTONIC, &time_store[0].start);
    for (int i=0; i < iteration; i++)
    {
        app_loggers[DEBUG]();
        app_loggers[INFO]();
        app_loggers[WARN]();
        app_loggers[ERR]();
        app_loggers[CRIT]();
    }
    clock_gettime(CLOCK_MONOTONIC, &time_store[0].end);

    clock_gettime(CLOCK_MONOTONIC, &time_store[1].start);
    for (int i=0; i < iteration; i++)
    {
        if (logger_mask & DEBUG)
            null_logger();

        if (logger_mask & INFO)
            null_logger();

        if (logger_mask & WARN)
            null_logger();

        if (logger_mask & ERR)
            null_logger();

        if (logger_mask & CRIT)
            null_logger();
    }
    clock_gettime(CLOCK_MONOTONIC, &time_store[1].end);

    for (int i=0; i < 2; i++)
    {
        printf("\n===============\n");
        printf("START = %lu - %lu\n", time_store[i].start.tv_sec, time_store[i].start.tv_nsec);
        printf("END   = %lu - %lu\n", time_store[i].end.tv_sec, time_store[i].end.tv_nsec);
        printf("\n===============\n");
    }
}

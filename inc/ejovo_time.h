#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct Clock {
    struct timeval start;
    struct timeval end;
} Clock;

Clock *Clock_new();

void Clock_tic(Clock *clock);

void Clock_toc(Clock *clock);

double elapsed_time(const Clock *clock);


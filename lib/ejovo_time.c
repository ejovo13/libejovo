#include "ejovo_time.h"

Clock *Clock_new() {
    Clock *out = malloc(sizeof(Clock));
    // out->start = malloc(sizeof(struct timeval));
    // out->end = malloc(sizeof(struct timeval));
    gettimeofday(&(out->start), 0);
    gettimeofday(&(out->end), 0);  
    return out;
}

// functional style that creates new data structures
void Clock_tic(Clock *clock) {
    gettimeofday(&(clock->start), 0);
}

void Clock_toc(Clock *clock) {
    gettimeofday(&(clock->end), 0);
}

double elapsed_time(const Clock *clock) {

    // time_t seconds = clock->end->tv_sec - clock->start->tv_sec;
    // time_t microseconds = clock->end->tv_usec - clock->start->tv_usec;
    time_t seconds = clock->end.tv_sec - clock->start.tv_sec;
    time_t microseconds = clock->end.tv_usec - clock->start.tv_usec;
    return seconds + microseconds * 1e-6;
}


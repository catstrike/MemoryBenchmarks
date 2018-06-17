#include <stdio.h>
#include "benchmark.h"

void report_elapsed_time(const char * tag, clock_t start, clock_t stop)
{
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("%s: %.2f ms\n", tag, elapsed);
}

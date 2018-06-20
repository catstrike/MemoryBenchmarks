//
//  Created by Lenar Sharipov on 07.06.18.
//  Copyright © 2018 Lenar. All rights reserved.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "platform/threads.h"
#include "platform/atomic.h"
#include "platform/memory.h"
#include "utility/benchmark.h"

#ifdef UNALIGNED
#define Offset -3
#else
#define Offset 0
#endif

#define Iterations 1000000

typedef struct {
    volatile int64_t * value;
    volatile int64_t brokenValues;
    volatile int64_t stopSignal;
} TaskParameters;

thread_ret_value writer(void * rawParameters)
{
    TaskParameters * parameters = (TaskParameters *)rawParameters;

    clock_t startTime = clock();

    for (size_t i = 0; i < Iterations; i += 1) {
        #ifdef LOCKED
        atomic_write(parameters->value, -1);
        atomic_write(parameters->value, 1);
        #else
        *parameters->value = -1;
        *parameters->value = 1;
        #endif
    }

    atomic_write(&parameters->stopSignal, 1);

    report_elapsed_time("Writer", startTime, clock());
    printf("Write cycles: %i\n", Iterations);

    END_THREAD;
}

thread_ret_value reader(void * rawParameters)
{
    TaskParameters * parameters = (TaskParameters *)rawParameters;

    clock_t startTime = clock();
    int64_t readCycles = 0;

    while (parameters->stopSignal != 1) {
        #ifdef LOCKED
        volatile int64_t value = atomic_read(parameters->value);
        #else
        volatile int64_t value = *parameters->value;
        #endif

        if (value != 1 && value != -1) {
            parameters->brokenValues += 1;
        }

        readCycles += 1;
    }

    report_elapsed_time("Reader", startTime, clock());
    printf("Read cycles: %lli\n", readCycles);

    END_THREAD;
}

int main(int argc, const char * argv[])
{
    size_t l2cacheSize;
    size_t cacheLineSize;

    if (0 != get_l2cache_size(&l2cacheSize)) {
        printf("Can't get the L2 cache size!");
        return 1;
    }

    if (0 != get_cache_line_size(&cacheLineSize)) {
        printf("Can't get the cache line size!");
        return 1;
    }

    printf("=======================================================\n");
    printf("L2 cache size: %zu, line size: %zu, total lines: %zu\n",
       l2cacheSize,
       cacheLineSize,
       l2cacheSize / cacheLineSize
    );

    printf("Flags: ");
    #ifdef UNALIGNED
    printf("UNALIGNED ");
    #endif

    #ifdef LOCKED
    printf("LOCKED ");
    #endif

    printf("\n");

    void * buffer = aligned_malloc(cacheLineSize * 2, cacheLineSize);
    void * beginningOfLine = buffer + cacheLineSize;
    volatile int64_t * variable = (int64_t*)(beginningOfLine + Offset);

    printf("Base address:            %zu\n", (size_t)buffer);
    printf("Beginning of the line:   %zu\n", (size_t)beginningOfLine);
    printf("Address of the variable: %zu\n", (size_t)variable);

    thread_type readerThread;
    thread_type writerThread;

    *variable = 1;

    TaskParameters parameters = {
      /* variable: */ variable,
      /* brokenValues: */ 0,
      /* stopSignal: */ 0
    };

    start_thread(&readerThread, reader, &parameters);
    start_thread(&writerThread, writer, &parameters);

    join_thread(readerThread);
    join_thread(writerThread);

    printf("Broken values count: %lli\n", parameters.brokenValues);

    free(buffer);

    return 0;
}

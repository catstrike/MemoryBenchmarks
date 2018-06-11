//
//  Created by Lenar Sharipov on 07.06.18.
//  Copyright © 2018 Lenar. All rights reserved.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "platform/threads.h"

#define CacheLineSize 64
#define CacheSize 4194304
#define CacheLines (CacheSize / CacheLineSize)
#define Offset -3
#define Iterations 1000000

typedef struct {
    volatile int64_t * value;
} TaskParameters;

thread_ret_value writer(void * rawParameters)
{
    TaskParameters * parameters = (TaskParameters *)rawParameters;

    printf("Writer started.\n");

    for (size_t i = 0; i < Iterations; i += 1) {
        *parameters->value = -1;
        *parameters->value = 1;
    }

    END_THREAD;
}

thread_ret_value reader(void * rawParameters)
{
    TaskParameters * parameters = (TaskParameters *)rawParameters;

    printf("Reader started.\n");

    for (size_t i = 0; i < Iterations; i += 1) {
        volatile int64_t value = *parameters->value;

        if (value != 1 && value != -1) {
            printf("Broken value! (%lli)\n", value);
        }
    }

    END_THREAD;
}

int main(int argc, const char * argv[])
{
    printf("=======================================================\n");
    printf("Cache size: %i, line size: %i, total lines: %i\n",
       CacheSize,
       CacheLineSize,
       CacheLines
    );

    void * buffer = malloc(CacheLineSize * 2);

    size_t beginningOfLine = ((size_t)buffer + CacheLineSize + 1) / CacheLineSize * CacheLineSize;
    int64_t * variable = (int64_t*)(beginningOfLine + Offset);

    printf("Base address:      %zu\n", (size_t)buffer);
    printf("Beginning of line: %zu\n", beginningOfLine);
    printf("Variable address:  %zu\n", (size_t)variable);

    thread_type readerThread;
    thread_type writerThread;

    *variable = 1;

    TaskParameters parameters = {variable};

    start_thread(&readerThread, reader, &parameters);
    start_thread(&writerThread, writer, &parameters);

    join_thread(readerThread);
    join_thread(writerThread);

    free(buffer);

    return 0;
}

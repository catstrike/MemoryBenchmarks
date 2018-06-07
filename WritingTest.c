//
//  Created by Lenar Sharipov on 07.06.18.
//  Copyright © 2018 Lenar. All rights reserved.
//

#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define CacheLineSize 64
#define CacheSize 4194304
#define CacheLines (CacheSize / CacheLineSize)
#define ThreadsCount 4

typedef struct {
    int64_t * buffer;
    size_t count;
} TaskParameters;

typedef void *(*ThreadStart) (void *);

int startThread(pthread_t * thread, ThreadStart start, void * parameters)
{
    pthread_attr_t attributes;

    int result;

    if ((result = pthread_attr_init(&attributes)) != 0) {
        return result;
    }

    if ((result = pthread_create(thread, &attributes, start, parameters)) != 0) {
        pthread_attr_destroy(&attributes);
        return result;
    }

    pthread_attr_destroy(&attributes);

    return result;
}

void reportElapsedTime(const char * tag, clock_t start, clock_t stop)
{
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("%s: %.2f ms\n", tag, elapsed);
}

clock_t WorkHard(int64_t* buffer, size_t count)
{
    size_t items = CacheLineSize / sizeof(int64_t);
    size_t rows = count / items;

    clock_t start = clock();

    for (size_t i = 0; i < items; i += 1) {
        for (size_t row = 0; row < rows; row += 1) {
            size_t offset = row * items + i;

            buffer[offset] = offset;
        }
    }

    clock_t stop = clock();

    reportElapsedTime("Hard", start, stop);

    return stop - start;
}

clock_t WorkFast(int64_t* buffer, size_t count)
{
    clock_t start = clock();

    for (size_t i = 0; i < count; i += 1) {
        buffer[i] = count - i;
    }

    clock_t stop = clock();

    reportElapsedTime("Fast", start, stop);

    return stop - start;
}

void * FastWorker(void * rawParameters)
{
    TaskParameters * parameters = (TaskParameters *)rawParameters;

    int64_t * buffer = parameters->buffer;
    size_t count = parameters->count;

    for (size_t i = 0; i < count; i += 1) {
        buffer[i] = count - i;
    }

    return NULL;
}

clock_t WorkFastThreaded(int64_t* buffer, size_t count)
{
    TaskParameters parameters[ThreadsCount];
    pthread_t threads[ThreadsCount];
    size_t countPerChunk = count / ThreadsCount;

    for (size_t i = 0; i < ThreadsCount; i += 1) {
        TaskParameters * parameter = &parameters[i];
        parameter->buffer = buffer + countPerChunk * i;
        parameter->count = countPerChunk;

        if ((errno = startThread(&threads[i], FastWorker, parameter)) != 0) {
            perror("Error!");
            printf("Can't start thread!\n");
        }
    }

    clock_t start = clock();

    for (size_t i = 0; i < ThreadsCount; i += 1) {
        pthread_join(threads[i], NULL);
    }

    clock_t stop = clock();

    reportElapsedTime("Fast (threaded)", start, stop);

    return stop - start;
}

int main(int argc, const char * argv[])
{
    printf("=======================================================\n");
    printf("Cache size: %i, line size: %i, total lines: %i\n",
       CacheSize,
       CacheLineSize,
       CacheLines
    );
    printf("Number of threads: %i\n", ThreadsCount);

    size_t size = CacheSize * CacheLineSize;
    int64_t* buffer = (int64_t*)malloc(size);
    int64_t* buffer2 = (int64_t*)malloc(size);
    int64_t* buffer3 = (int64_t*)malloc(size);
    size_t count = size / sizeof(int64_t);

    clock_t start = clock();

    clock_t fastTime = WorkFast(buffer, count);
    clock_t fastTimeThreaded = WorkFastThreaded(buffer2, count);
    clock_t hardTime = WorkHard(buffer3, count);

    clock_t stop = clock();

    printf("-------------------------------------------------------\n");
    reportElapsedTime("Total", start, stop);

    double percent = (1.0 - (double)fastTime / hardTime) * 100;
    double percentThreaded = (1.0 - (double)fastTimeThreaded / hardTime) * 100;

    printf("WorkFast is faster then WorkHard by %.2f%%\n", percent);
    printf("WorkFastThreaded is faster then WorkHard by %.2f%%\n", percentThreaded);

    return 0;
}

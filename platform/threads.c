#include "threads.h"

int start_thread(thread_type * thread, thread_start_t start, void * parameters)
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

void join_thread(thread_type thread)
{
    pthread_join(thread, NULL);
}

#ifndef __PLATFORM_THREADS_H__
#define __PLATFORM_THREADS_H__

#include <pthread.h>

typedef void* thread_ret_value;
typedef pthread_t thread_type;

typedef thread_ret_value(*thread_start_t) (void *);
int start_thread(thread_type * thread, thread_start_t start, void * parameters);
void join_thread(thread_type thread);

#define END_THREAD return 0

#endif // __PLATFORM_THREADS_H__

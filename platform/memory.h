#ifndef __PLATFORM_MEMORY_H__
#define __PLATFORM_MEMORY_H__

#include <stdlib.h>

int get_l2cache_size(size_t * size);
int get_cache_line_size(size_t * size);

void * aligned_malloc(size_t size, size_t alignment);

#endif // __PLATFORM_MEMORY_H__

#include "memory.h"
#include <sys/sysctl.h>

int get_l2cache_size(size_t * size)
{
    size_t valueSize;
    *size = 0;
    sysctlbyname("hw.l2cachesize", NULL, &valueSize, NULL, 0);
    return sysctlbyname("hw.l2cachesize", size, &valueSize, NULL, 0);
}

int get_cache_line_size(size_t * size)
{
    size_t valueSize;
    *size = 0;
    sysctlbyname("hw.cachelinesize", NULL, &valueSize, NULL, 0);
    return sysctlbyname("hw.cachelinesize", size, &valueSize, NULL, 0);
}

void * aligned_malloc(size_t size, size_t alignment)
{
    void * result;

    if (0 != posix_memalign(&result, alignment, size)) {
        return NULL;
    }

    return result;
}

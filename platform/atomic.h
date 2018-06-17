#ifndef __PLATFORM_ATOMIC_H__
#define __PLATFORM_ATOMIC_H__

void atomic_write(volatile int64_t * targetAddress, int64_t value);
int64_t atomic_read(volatile int64_t * sourceAddress);

#endif // __PLATFORM_ATOMIC_H__

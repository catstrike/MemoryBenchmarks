#include <stdlib.h>
#include "atomic.h"

void atomic_write(volatile int64_t * targetAddress, int64_t value)
{
    asm volatile (
      "XCHGQ %%rax, (%%rdx)"
      : "+a" (value),
        "+d" (targetAddress)
      : /* input */
      : /* clobbed list */
    );
}

int64_t atomic_read(volatile int64_t * sourceAddress)
{
    int64_t result = 0;

    asm volatile (
      "XOR %%rax, %%rax;\n"
      "LOCK CMPXCHGQ %%rax, (%%rdx);\n"
      : "+d" (sourceAddress),
        "=a" (result)
      : /* input */
      : /* clobbed list */
    );

    return result;
}

#include "../include/dynarray.h"

void kuDynarray_clear(
    void *ptr
)
{
    if (!ptr) {
        return;
    }
    kuDynarray_getHeader(ptr)->load = 0;
}

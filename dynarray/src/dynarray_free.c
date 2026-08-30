#include "../include/dynarray.h"
#include <stdlib.h>

void kuDynarray_free(
    void *ptr
)
{
    if (!ptr) {
        return;
    }
    free(kuDynarray_getHeader(ptr));
}

#include "../include/dynarray.h"
#include <stdlib.h>

int __kuDynarray_pushBack(
    void **ptr,
    const void *e
)
{
    if (!ptr || !*ptr) {
        return -1;
    }
    kuDynarrayHeader* h = kuDynarray_getHeader(*ptr);
    if (!h) {
        return -1;
    }
    if (h->load == h->size) {
        // Push
    }
    return 0;
}

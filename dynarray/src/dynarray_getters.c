#include "../include/dynarray.h"

kuDynarrayHeader* kuDynarray_getHeader(
    const void *ptr
)
{
    if (!ptr) {
        return NULL;
    }
    return ((kuDynarrayHeader *)ptr) - 1;
}

size_t kuDynarray_getSize(
    const void *ptr
)
{
    if (!ptr) {
        return NULL;
    }
    return kuDynarray_getHeader(ptr)->size;
}

size_t kuDynarray_getLoad(
    const void *ptr
)
{
    if (!ptr) {
        return NULL;
    }
    return kuDynarray_getHeader(ptr)->load;
}

size_t kuDynarray_getTypeSize(
    const void *ptr
)
{
    if (!ptr) {
        return NULL;
    }
    return kuDynarray_getHeader(ptr)->type;
}

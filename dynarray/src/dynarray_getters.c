#include "../include/dynarray.h"

void* __kuDynarray_at(
    const void *ptr,
    size_t idx
)
{
    kuDynarrayHeader *header = kuDynarray_getHeader(ptr);

    if (!header || idx >= header->load) {
        return NULL;
    }
    return (char *)ptr + (idx * header->type);
}

void* __kuDynarray_last(
    const void *ptr
)
{
    kuDynarrayHeader *header = kuDynarray_getHeader(ptr);

    if (!header || header->load == 0) {
        return NULL;
    }
    return __kuDynarray_at(ptr, header->load - 1);
}

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
        return 0;
    }
    return kuDynarray_getHeader(ptr)->size;
}

size_t kuDynarray_getLoad(
    const void *ptr
)
{
    if (!ptr) {
        return 0;
    }
    return kuDynarray_getHeader(ptr)->load;
}

size_t kuDynarray_getTypeSize(
    const void *ptr
)
{
    if (!ptr) {
        return 0;
    }
    return kuDynarray_getHeader(ptr)->type;
}

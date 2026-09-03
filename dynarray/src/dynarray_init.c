#include "../include/dynarray.h"
#include <stdint.h>
#include <stdlib.h>

int __kuDynarray_init(
    void **ptr,
    size_t initialSize,
    size_t typesize
)
{
    kuDynarrayHeader* header = NULL;

    if (!ptr || typesize == 0 || initialSize == 0 ||
        initialSize > (SIZE_MAX - sizeof(kuDynarrayHeader)) / typesize) {
        return -1;
    }
    header = malloc(sizeof(kuDynarrayHeader) + (initialSize * typesize));
    if (!header) {
        return -1;
    }
    header->load = 0;
    header->size = initialSize;
    header->type = typesize;
    *ptr = (void *)(header + 1);
    return 0;
}

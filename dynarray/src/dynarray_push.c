#include "../include/dynarray.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int __kuDynarray_pushBack(
    void **ptr,
    const void *e
)
{
    if (!ptr || !*ptr || !e) {
        return -1;
    }
    kuDynarrayHeader* h = kuDynarray_getHeader(*ptr);
    if (!h) {
        return -1;
    }
    if (h->load == h->size) {
        size_t newSize = h->size > SIZE_MAX / 2 ? SIZE_MAX : h->size * 2;
        kuDynarrayHeader *resized;

        if (newSize == h->size ||
            newSize > (SIZE_MAX - sizeof(kuDynarrayHeader)) / h->type) {
            return -1;
        }
        resized = realloc(h, sizeof(kuDynarrayHeader) + (newSize * h->type));
        if (!resized) {
            return -1;
        }
        h = resized;
        h->size = newSize;
        *ptr = (void *)(h + 1);
    }
    memcpy((char *)*ptr + (h->load * h->type), e, h->type);
    h->load++;
    return 0;
}

void __kuDynarray_popBack(
    void **ptr
)
{
    kuDynarrayHeader *header;

    if (!ptr || !*ptr) {
        return;
    }
    header = kuDynarray_getHeader(*ptr);
    if (header && header->load > 0) {
        header->load--;
    }
}

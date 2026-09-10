#include "../include/dynarray.h"
#include <stdint.h>
#include <stdlib.h>

int __kuDynarray_resize(
	void **ptr,
	size_t newSize
)
{
	kuDynarrayHeader *header;
	kuDynarrayHeader *resized;

	if (!ptr || !*ptr || newSize == 0) {
		return -1;
	}
	header = kuDynarray_getHeader(*ptr);
	if (!header || newSize > (SIZE_MAX - sizeof(kuDynarrayHeader)) / header->type) {
		return -1;
	}
	resized = realloc(header,
		sizeof(kuDynarrayHeader) + (newSize * header->type));
	if (!resized) {
		return -1;
	}
	resized->size = newSize;
	if (resized->load > newSize) {
		resized->load = newSize;
	}
	*ptr = (void *)(resized + 1);
	return 0;
}

#include <kronklab/kronklab.h>
#include <dynarray.h>

Test(dynarray, init)
{
    int *values = NULL;

    AssertEq(kuDynarray_init(&values, 2, int), 0,
        "initialization should succeed");
    AssertNotNull(values, "initialization should allocate data");
    AssertEq(kuDynarray_getSize(values), 2,
        "initial capacity should be preserved");
    AssertEq(kuDynarray_getLoad(values), 0,
        "a new array should be empty");
    AssertEq(kuDynarray_getTypeSize(values), sizeof(int),
        "element size should be preserved");
    AssertEq(kuDynarray_getHeader(values)->load, 0,
        "header load should match the public getter");
    kuDynarray_free(values);
}

Test(dynarray, push_and_access)
{
    int *values = NULL;

    AssertEq(kuDynarray_init(&values, 2, int), 0,
        "initialization should succeed");
    AssertEq(kuDynarray_pushBack(values, 10), 0,
        "first push should succeed");
    AssertEq(kuDynarray_pushBack(values, 20), 0,
        "second push should succeed");
    AssertEq(kuDynarray_pushBack(values, 30), 0,
        "push should grow a full array");
    AssertEq(kuDynarray_getSize(values), 4,
        "full arrays should grow geometrically");
    AssertEq(kuDynarray_getLoad(values), 3,
        "load should count pushed elements");
    AssertEq(*kuDynarray_at(values, 0), 10,
        "at should return the first element");
    AssertEq(*kuDynarray_at(values, 2), 30,
        "at should return the requested element");
    AssertEq(*kuDynarray_last(values), 30,
        "last should return the final element");
    kuDynarray_free(values);
}

Test(dynarray, pop_clear_and_bounds)
{
    int *values = NULL;

    AssertEq(kuDynarray_init(&values, 1, int), 0,
        "initialization should succeed");
    AssertEq(kuDynarray_at(values, 0), NULL,
        "an empty array should have no accessible elements");
    AssertEq(kuDynarray_last(values), NULL,
        "an empty array should have no last element");
    AssertEq(kuDynarray_pushBack(values, 42), 0,
        "push should succeed");
    AssertEq(kuDynarray_at(values, 1), NULL,
        "out-of-bounds access should return null");
    kuDynarray_popBack(values);
    AssertEq(kuDynarray_getLoad(values), 0,
        "pop should remove the final element");
    kuDynarray_popBack(values);
    AssertEq(kuDynarray_getLoad(values), 0,
        "pop on an empty array should be harmless");
    kuDynarray_clear(values);
    AssertEq(kuDynarray_getLoad(values), 0,
        "clear should empty the array");
    kuDynarray_free(values);
}

Test(dynarray, invalid_init)
{
    int *values = NULL;

    AssertNe(kuDynarray_init(NULL, 2, int), 0,
        "a null output pointer should fail");
    AssertNe(kuDynarray_init(&values, 0, int), 0,
        "zero capacity should fail");
    AssertNe(__kuDynarray_init((void **)&values, 2, 0), 0,
        "zero-sized elements should fail");
}

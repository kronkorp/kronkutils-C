#include <kronklab/kronklab.h>
#include "dynarray.h"

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

Test(dynarray, resize_direct_assignment)
{
    int *values = NULL;

    AssertEq(kuDynarray_init(&values, 1, int), 0,
        "initialization should succeed");
    AssertEq(kuDynarray_resize(values, 2), 0,
        "resize should increase capacity");
    values[1] = 42;
    AssertEq(values[1], 42,
        "a caller should be able to assign directly by index");
    AssertEq(kuDynarray_getSize(values), 2,
        "resize should update capacity");
    AssertEq(kuDynarray_getLoad(values), 0,
        "direct assignment should not change the tracked load");
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

Test(dynarray, getters_return_zero_on_null)
{
    AssertEq(kuDynarray_getSize(NULL), 0,
        "size of a null array should be zero");
    AssertEq(kuDynarray_getLoad(NULL), 0,
        "load of a null array should be zero");
    AssertEq(kuDynarray_getTypeSize(NULL), 0,
        "type size of a null array should be zero");
    AssertNull(kuDynarray_getHeader(NULL),
        "header of a null array should be null");
}

Test(dynarray, accessors_null_or_oob)
{
    int *values = NULL;

    AssertNull(kuDynarray_at(values, 0),
        "at on a null array should return null");
    AssertNull(kuDynarray_last(values),
        "last on a null array should return null");
    AssertEq(kuDynarray_init(&values, 2, int), 0,
        "initialization should succeed");
    AssertNull(__kuDynarray_at(values, (size_t)-1),
        "an absurdly large index should return null");
    kuDynarray_free(values);
}

Test(dynarray, free_and_clear_are_null_safe)
{
    kuDynarray_free(NULL);
    kuDynarray_clear(NULL);
    AssertEq(kuDynarray_getLoad(NULL), 0,
        "the process should still be alive after null free/clear");
}

Test(dynarray, pushback_invalid_args)
{
    int *values = NULL;
    int value = 1;

    AssertNe(__kuDynarray_pushBack(NULL, &value), 0,
        "a null pointer-to-array should fail");
    AssertNe(__kuDynarray_pushBack((void **)&values, &value), 0,
        "pushing into an uninitialized (null) array should fail");
    AssertEq(kuDynarray_init(&values, 2, int), 0,
        "initialization should succeed");
    AssertNe(__kuDynarray_pushBack((void **)&values, NULL), 0,
        "pushing a null element should fail");
    kuDynarray_free(values);
}

Test(dynarray, popback_is_null_safe)
{
    int *values = NULL;

    __kuDynarray_popBack(NULL);
    __kuDynarray_popBack((void **)&values);
    AssertEq(kuDynarray_init(&values, 1, int), 0,
        "initialization should succeed");
    kuDynarray_popBack(values);
    AssertEq(kuDynarray_getLoad(values), 0,
        "popping an empty array should stay at zero load");
    kuDynarray_free(values);
}

Test(dynarray, capacity_grows_geometrically)
{
    int *values = NULL;

    AssertEq(kuDynarray_init(&values, 1, int), 0,
        "initialization should succeed");
    for (int i = 0; i < 8; i++) {
        AssertEq(kuDynarray_pushBack(values, i), 0,
            "push should keep succeeding");
    }
    AssertEq(kuDynarray_getLoad(values), 8,
        "load should equal the number of pushes");
    AssertEq(kuDynarray_getSize(values), 8,
        "capacity should have doubled to exactly fit eight elements");
    AssertEq(kuDynarray_pushBack(values, 8), 0,
        "a ninth push should trigger another growth");
    AssertEq(kuDynarray_getSize(values), 16,
        "capacity should double again once full");
    kuDynarray_free(values);
}

Test(dynarray, pop_then_push_reuses_slot)
{
    int *values = NULL;

    AssertEq(kuDynarray_init(&values, 4, int), 0,
        "initialization should succeed");
    AssertEq(kuDynarray_pushBack(values, 1), 0, "push should succeed");
    AssertEq(kuDynarray_pushBack(values, 2), 0, "push should succeed");
    AssertEq(kuDynarray_pushBack(values, 3), 0, "push should succeed");
    kuDynarray_popBack(values);
    AssertEq(kuDynarray_getSize(values), 4,
        "popping should not shrink the allocated capacity");
    AssertEq(kuDynarray_getLoad(values), 2,
        "popping should decrement the load");
    AssertEq(kuDynarray_pushBack(values, 99), 0,
        "pushing after a pop should reuse the freed slot");
    AssertEq(kuDynarray_getSize(values), 4,
        "reusing a freed slot should not trigger a growth");
    AssertEq(*kuDynarray_at(values, 2), 99,
        "the reused slot should hold the newly pushed value");
    kuDynarray_free(values);
}

Test(dynarray, clear_preserves_capacity)
{
    int *values = NULL;

    AssertEq(kuDynarray_init(&values, 2, int), 0,
        "initialization should succeed");
    AssertEq(kuDynarray_pushBack(values, 1), 0, "push should succeed");
    AssertEq(kuDynarray_pushBack(values, 2), 0, "push should succeed");
    AssertEq(kuDynarray_pushBack(values, 3), 0, "push should succeed");
    AssertEq(kuDynarray_getSize(values), 4,
        "capacity should have grown before clearing");
    kuDynarray_clear(values);
    AssertEq(kuDynarray_getLoad(values), 0,
        "clear should reset load to zero");
    AssertEq(kuDynarray_getSize(values), 4,
        "clear should keep the grown capacity");
    AssertEq(kuDynarray_pushBack(values, 42), 0,
        "pushing after clear should succeed");
    AssertEq(*kuDynarray_at(values, 0), 42,
        "the first slot should be reused after clear");
    kuDynarray_free(values);
}

Test(dynarray, last_updates_after_pop)
{
    int *values = NULL;

    AssertEq(kuDynarray_init(&values, 4, int), 0,
        "initialization should succeed");
    AssertEq(kuDynarray_pushBack(values, 1), 0, "push should succeed");
    AssertEq(kuDynarray_pushBack(values, 2), 0, "push should succeed");
    AssertEq(kuDynarray_pushBack(values, 3), 0, "push should succeed");
    AssertEq(*kuDynarray_last(values), 3,
        "last should be the most recently pushed value");
    kuDynarray_popBack(values);
    AssertEq(*kuDynarray_last(values), 2,
        "last should fall back to the previous element after a pop");
    kuDynarray_free(values);
}

Test(dynarray, supports_double_type)
{
    double *values = NULL;

    AssertEq(kuDynarray_init(&values, 2, double), 0,
        "initialization should succeed");
    AssertEq(kuDynarray_getTypeSize(values), sizeof(double),
        "type size should match double");
    AssertEq(kuDynarray_pushBack(values, 3.14), 0, "push should succeed");
    AssertEq(kuDynarray_pushBack(values, 2.71), 0, "push should succeed");
    AssertEq(*kuDynarray_at(values, 0), 3.14,
        "double precision should be preserved");
    AssertEq(*kuDynarray_last(values), 2.71,
        "last double value should be preserved");
    kuDynarray_free(values);
}

Test(dynarray, supports_struct_type)
{
    typedef struct {
        int id;
        double weight;
    } Item;

    Item *items = NULL;
    Item first = { 1, 4.5 };
    Item second = { 2, 9.0 };

    AssertEq(kuDynarray_init(&items, 2, Item), 0,
        "initialization should succeed");
    AssertEq(kuDynarray_getTypeSize(items), sizeof(Item),
        "type size should match the struct size");
    AssertEq(kuDynarray_pushBack(items, first), 0,
        "pushing a struct by value should succeed");
    AssertEq(kuDynarray_pushBack(items, second), 0,
        "pushing a second struct should succeed");
    AssertEq(kuDynarray_at(items, 0)->id, 1,
        "first struct field should be preserved");
    AssertEq(kuDynarray_last(items)->weight, 9.0,
        "last struct's field should be preserved");
    kuDynarray_free(items);
}

Test(dynarray, stress_many_elements_roundtrip)
{
    int *values = NULL;
    const int count = 1000;

    AssertEq(kuDynarray_init(&values, 1, int), 0,
        "initialization should succeed");
    for (int i = 0; i < count; i++) {
        AssertEq(kuDynarray_pushBack(values, i), 0,
            "every push in the stress test should succeed");
    }
    AssertEq(kuDynarray_getLoad(values), (size_t)count,
        "load should equal the number of pushed elements");
    AssertGe(kuDynarray_getSize(values), kuDynarray_getLoad(values),
        "capacity should always be at least the load");
    for (int i = 0; i < count; i++) {
        AssertEq(*kuDynarray_at(values, i), i,
            "every element should keep its pushed value");
    }
    kuDynarray_free(values);
}

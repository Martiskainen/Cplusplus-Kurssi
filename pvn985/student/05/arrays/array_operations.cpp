#include "array_operations.hh"
/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int size: number of elements to be examined
 * return value: the greatest element of the array
 */
int greatest_v1(int* itemptr, int size)
{
    int greatest = *itemptr;
    ++itemptr;

    for (int i = 0; i < size - 1; i++)
    {
        if (*itemptr > greatest)
        {
            greatest = *itemptr;
        }
        ++itemptr;
    }
    return greatest;
}

/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int* endptr: pointer to the memory address after the last element of the array
 * return value: the greatest element of the array
 */
int greatest_v2(int* itemptr, int* endptr)
{
    int greatest = *itemptr;
    ++itemptr;

    while (itemptr < endptr)
    {
        if (*itemptr > greatest)
        {
            greatest = *itemptr;
        }
        ++itemptr;
    }

    return greatest;
}

/* Copies the content of the array to another array
 * int* itemptr: pointer to the first array element to be copied
 * int* endptr: pointer to the memory address after the last element of the array to be copied
 * int* targetptr: pointer to the head of the array, to which to copy
 */
void copy(int* itemptr, int* endptr, int* targetptr)
{
    while (itemptr < endptr)
    {
        *targetptr = *itemptr;
        ++itemptr;
        ++targetptr;
    }
}

/* Reverses the elements of the array
 * int* leftptr: pointer to the first element of the reversable part
 * int* rightptr: pointer to the next memory address after the reversable part
 */
void reverse(int* leftptr, int* rightptr)
{
    --rightptr;
    while (leftptr < rightptr)
    {
        int tmp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = tmp;

        ++leftptr;
        --rightptr;
    }
}

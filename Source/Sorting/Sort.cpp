#include "PCH.h"
#include "Sort.h"

void Sort::MergeSort(int array[], const int start, const int end)
{
    const int size {end - start};

    if(size < 1)
    {
        return;
    }

    const int mid {start + size / 2};
    MergeSort(array, start, mid);
    MergeSort(array, mid + 1, end);
    Merge(array, start, mid, end);
}

void Sort::Merge(int array[], const int start, const int mid, const int end)
{
    const int lhsSize {mid - start + 1};
    const int rhsSize {end - mid};

    int* lhs = new int[lhsSize];
    int* rhs = new int[rhsSize];

    for (auto i = 0; i < lhsSize; i++)
    {
        lhs[i] = array[start + i];

        if(i < rhsSize)
        {
            rhs[i] = array[(mid + 1) + i];
        }
    }

    int lhsIndex {0}, rhsIndex {0}, arrayIndex {start};

    while(lhsIndex < lhsSize && rhsIndex < rhsSize)
    {
        array[arrayIndex++] = lhs[lhsIndex] >= rhs[rhsIndex] ? rhs[rhsIndex++] : lhs[lhsIndex++];
    }
    while (rhsIndex < rhsSize)
    {
        array[arrayIndex++] = rhs[rhsIndex++];
    }
    while (lhsIndex < lhsSize)
    {
        array[arrayIndex++] = lhs[lhsIndex++];
    }

    delete[] lhs;
    delete[] rhs;
}
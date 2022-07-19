#include "PCH.h"
#include "Inversion.h"

uint64_t Inversion::InversionPairCount(int array[], const int start, const int end)
{
    const int size {end - start};

    if(size < 1)
    {
        return 0;
    }

    uint64_t inversionCount {0};
    const int mid {start + size / 2};

    inversionCount += InversionPairCount(array, start, mid);
    inversionCount += InversionPairCount(array, mid + 1, end);
    inversionCount += Count(array, start, mid, end);

    return inversionCount;
}

uint64_t Inversion::Count(int array[], const int start, const int mid, const int end)
{
    uint64_t inversionCount {0};

    const int lhsSize {mid - start + 1};
    const int rhsSize {end - mid};

    int* lhs = new int[lhsSize];
    int* rhs = new int[rhsSize];

    for (auto i = 0; i < lhsSize; i++)
    {
        lhs[i] = array[start + i];

        if (i < rhsSize)
        {
            rhs[i] = array[(mid + 1) + i];
        }
    }

    int lhsIndex {0}, rhsIndex {0}, arrayIndex {start};

    while(lhsIndex < lhsSize && rhsIndex < rhsSize)
    {
        if(lhs[lhsIndex] >= rhs[rhsIndex])
        {
            array[arrayIndex++] = rhs[rhsIndex++];

            // Since rhs value is lower it will form inversion pair with all the leftover lhs elements.
            inversionCount += lhsSize - lhsIndex;


        }
        else
        {
            array[arrayIndex++] = lhs[lhsIndex++];
        }
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

    return inversionCount;
}
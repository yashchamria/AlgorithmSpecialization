#include "PCH.h"
#include "Sort.h"
#include "Util.h"

namespace Course01
{
    void Sort::QuickSort(int array[], const int start, const int end)
    {
        if (start >= end) { return; }

        // To select median of three elements (first, middle, last) as pivot.
        const int size = end - start + 1;
        if(const int mid = start + (size % 2 == 0 ? size / 2 - 1 : size / 2);
            IsMedian(array[mid], array[start], array[end]))
        {
            Swap(array[mid], array[end]);
        }
        else if (IsMedian(array[start], array[mid], array[end]))
        {
            Swap(array[start], array[end]);
        }

        // To select first element as pivot.
        //Swap(array[end], array[start]);

        // To select last element as pivot.
        const int pivotIndex {end};

        int minIndex {start};
        for (int i = minIndex; i < end; ++i)
        {
            if (array[i] < array[pivotIndex])
            {
                Swap(array[minIndex], array[i]);
                ++minIndex;
            }
        }
        Swap(array[minIndex], array[pivotIndex]);

        QuickSort(array, start, minIndex - 1);
        QuickSort(array, minIndex + 1, end);
    }

    void Sort::MergeSort(int array[], const int start, const int end)
    {
        const int size{ end - start };

        if (size < 1)
        {
            return;
        }

        const int mid{ start + size / 2 };
        MergeSort(array, start, mid);
        MergeSort(array, mid + 1, end);
        Merge(array, start, mid, end);
    }

    void Sort::Merge(int array[], const int start, const int mid, const int end)
    {
        const int lhsSize{ mid - start + 1 };
        const int rhsSize{ end - mid };

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

        int lhsIndex{ 0 }, rhsIndex{ 0 }, arrayIndex{ start };

        while (lhsIndex < lhsSize && rhsIndex < rhsSize)
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
}
#include "PCH.h"
#include "Selection.h"
#include "Util.h"

int Selection::QuickSelect(int array[], const int start, const int end, const int order)
{
    if (order < 0 || order > end - start + 1)
    {
        std::cout << "Order is out of bound.\n";
        return INT_MAX;
    }

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

    if (minIndex - start > order) // left array
    {
        return QuickSelect(array, start, minIndex - 1, order);
    }
    if(minIndex - start < order) // right array
    {
        return QuickSelect(array, minIndex + 1, end,order + start - (minIndex + 1));
    }
    return array[minIndex];
}
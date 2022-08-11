#pragma once

namespace Course01
{
    class Sort final
    {
    public:
        static void QuickSort(int array[], const int start, const int end);
        static void MergeSort(int array[], const int start, const int end);

    private:
        static void Merge(int array[], const int start, const int mid, const int end);

    private:
        static bool IsMedian(const int value, const int lhs, const int rhs) { return (value < lhs&& value > rhs) || (value > lhs && value < rhs); }
    };
}
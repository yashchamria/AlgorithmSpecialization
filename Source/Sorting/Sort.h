#pragma once

class Sort final
{
public:
    static void QuickSort(int array[], const int start, const int end);

private:
    static void Swap(int& lhs, int& rhs);
    static bool IsMedian(int const value, int const lhs, int const rhs);

public:
    static void MergeSort(int array[], const int start, const int end);

private:
    static void Merge(int array[], const int start, const int mid, const int end);


};
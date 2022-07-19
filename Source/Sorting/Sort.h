#pragma once

class Sort final
{
public:
    static void MergeSort(int array[], const int start, const int end);

private:
    static void Merge(int array[], const int start, const int mid, const int end);
};
/******************************************************************************************
********* Divide and Conquer, Sorting and Searching, and Randomized Algorithms ************
******************************************************************************************/

/************************************* Quick Sort ****************************************/

#include <fstream>
#include <iostream>
#include <vector>

bool IsMedian(const int value, const int lhs, const int rhs) { return (value < lhs&& value > rhs) || (value > lhs && value < rhs); }

void Swap(int& lhs, int& rhs)
{
    const int temp = lhs;
    lhs = rhs;
    rhs = temp;
}

void QuickSort(int array[], const int start, const int end)
{
    if (start >= end) { return; }

    // To select median of three elements (first, middle, last) as pivot.
    //const int size = end - start + 1;
    //const int mid = start + (size % 2 == 0 ? size / 2 - 1 : size / 2);
    //if (IsMedian(array[mid], array[start], array[end]))
    //{
    //    Swap(array[mid], array[end]);
    //}
    //else if (IsMedian(array[start], array[mid], array[end]))
    //{
    //    Swap(array[start], array[end]);
    //}

    // To select first element as pivot.
    //Swap(array[end], array[start]);

    // To select last element as pivot.
    const int pivotIndex {end};

    int minIndex{ start };
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

int main()
{
    std::cout << "Reading file...\r";
    std::ifstream inputFile{ "../QuickSort/unsortedArray.txt", std::ios::in };
    if (!inputFile.is_open())
    {
        std::cout << "Failed to open the file!\n";
        return -1;
    }

    int num{};
    std::vector<int> input{};
    while (inputFile >> num)
    {
        input.push_back(num);
    }
    inputFile.close();

    if (!input.empty())
    {
        std::cout << "Sorting the array...\r";
        QuickSort(&input[0], 0, (int)input.size() - 1);

        std::cout << "Array sorted successfully.\n";
        std::cout << "Outputting file...\r";

        if (std::fstream outputFile{ "../QuickSort/result_sortedArray.txt", std::ios::out }; outputFile.is_open())
        {
            for (const int number : input)
            {
                outputFile << number << "\n";
            }
            outputFile.close();

            std::cout << "Output file saved.\n";
        }
        else
        {
            std::cout << "Failed to save the output file!\n";
        }
    }

    std::cin.get();
    return 0;
}
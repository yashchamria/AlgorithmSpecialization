/******************************************************************************************
********* Divide and Conquer, Sorting and Searching, and Randomized Algorithms ************
******************************************************************************************/

/************************************* Merge Sort ****************************************/

#include <fstream>
#include <iostream>
#include <vector>

void Merge(int array[], const int start, const int mid, const int end)
{
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

void MergeSort(int array[], const int start, const int end)
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

int main()
{
    std::cout << "Reading file...\r";
    std::ifstream inputFile{ "../MergeSort/unsortedArray.txt", std::ios::in };
    if (!inputFile.is_open())
    {
        std::cout << "Failed to open the file!\n";
        return -1;
    }

    int num {};
    std::vector<int> input{};

    while (inputFile >> num)
    {
        input.push_back(num);
    }
    inputFile.close();

    if (!input.empty())
    {
        std::cout << "Sorting the array...\r";
        MergeSort(&input[0], 0, (int)input.size() - 1);

        std::cout << "Array sorted successfully.\n";
        std::cout << "Outputting file...\r";

        if (std::fstream outputFile{ "../MergeSort/result_sortedArray.txt", std::ios::out }; outputFile.is_open())
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

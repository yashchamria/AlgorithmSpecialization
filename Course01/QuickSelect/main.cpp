/******************************************************************************************
******************* Graph Search, Shortest Paths, and Data Structures *********************
******************************************************************************************/

/************************************ Quick Select ***************************************/

#include <fstream>
#include <iostream>
#include <vector>

void Swap(int& lhs, int& rhs)
{
    const int temp = lhs;
    lhs = rhs;
    rhs = temp;
}

int QuickSelect(int array[], const int start, const int end, const int order)
{
    if (order < 0 || order > end - start + 1)
    {
        std::cout << "Order is out of bound.\n";
        return INT_MAX;
    }

    const int pivotIndex{ end };
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

    if (minIndex - start > order) // left array
    {
        return QuickSelect(array, start, minIndex - 1, order);
    }
    if (minIndex - start < order) // right array
    {
        return QuickSelect(array, minIndex + 1, end, order + start - (minIndex + 1));
    }
    return array[minIndex];
}

int main()
{
    std::cout << "Reading file...\r";
    std::ifstream inputFile{ "../QuickSelect/unsortedArray.txt", std::ios::in };
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
        constexpr int order = 10003;
        std::cout << "Finding the element...\r";
        const int element = QuickSelect(input.data(), 0, (int)input.size() - 1, order);

        std::cout << "Element order : " << order << ", value : " << element << "\n";
    }

    std::cin.get();
    return 0;
}
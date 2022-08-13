/******************************************************************************************
******************* Graph Search, Shortest Paths, and Data Structures *********************
******************************************************************************************/

/*************************************** Heap Sort ***************************************/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void Swap(int& lhs, int& rhs)
{
	const int temp = lhs;
	lhs = rhs;
	rhs = temp;
}

void HeapSort(int data[], const int size)
{
	const auto heapify = [](auto const& heapify_ref, int data[], const int start, const int end) -> void
	{
		int child = 2 * start + 1;
		if (child > end) { return; }

		if(child + 1 <= end && data[child + 1] > data[child])
		{
			++child; // right child.
		}

		if(data[child] > data[start])
		{
			Swap(data[start], data[child]);
			heapify_ref(heapify_ref, data, child, end);
		}
	};

	for (int i = size - 1; i >= 0; --i)
	{
		heapify(heapify, data, i, size - 1);
	}

	for (int i = size - 1; i > 0; --i)
	{
		Swap(data[0], data[i]);
		heapify(heapify, data, 0, i - 1);
	}
}

int main()
{
	// Reading the file.
	std::cout << "Reading data...\r";
	std::ifstream inputFile{ "../HeapSort/UnsortedArray.txt", std::ios::in };
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open the file!\n";
		return -1;
	}
	
	std::vector<int> data;
	for (std::string line; std::getline(inputFile, line);)
	{
		std::istringstream lineStream {line};
		int number {0};
		lineStream >> number;
		data.push_back(number);
	}
	inputFile.close();

	HeapSort(data.data(), data.size());

	for(int i = 0; i < data.size(); ++i)
	{
		std::cout << data[i] << (data.size() - i == 1 ? "." : ", ");
	}

	std::cin.get();
    return 0;
}
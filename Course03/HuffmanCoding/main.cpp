/******************************************************************************************
********** Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming *************
******************************************************************************************/

/**************************** Huffman's coding algorithm **********************************/

#include <fstream>
#include <iostream>
#include <queue>
#include <ranges>
#include <vector>

using Symbol = uint32_t;
using Frequency = uint32_t;
using Data = std::pair<Symbol, Frequency>;

using Bits = std::vector<bool>;
using HuffmanCode = std::pair<Symbol, Bits>;

struct HuffmanNode
{
	const Symbol symbol;
	const Frequency frequency;
	const HuffmanNode *left, *right;

	HuffmanNode(const Symbol symbol, const Frequency frequency, const HuffmanNode* left = nullptr, const HuffmanNode* right = nullptr)
	: symbol(symbol), frequency(frequency), left(left), right(right) {}
};

void GetLeafCodes(std::vector<HuffmanCode>& codes, const HuffmanNode* node, Bits bits)
{
	if (!node->left && !node->right)
	{
		codes.emplace_back(node->symbol, bits);
		return;
	}

	if (node->left)
	{
		bits.push_back(false);
		GetLeafCodes(codes, node->left, bits);
	}

	if (node->right)
	{
		bits[bits.size() - 1] = true;
		GetLeafCodes(codes, node->right, bits);
	}
};

std::vector<HuffmanCode> GetHuffmanCodes(std::vector<Data>& data)
{
	std::ranges::sort(data, [](const auto& data1, const auto& data2) { return data1.second < data2.second;});

	std::queue<HuffmanNode*> leafNodes;
	std::queue<HuffmanNode*> parentNodes;

	for (const auto& entry : data)
	{
		leafNodes.emplace(new HuffmanNode(entry.first, entry.second));
	}

	const auto extractMin = [&]
	{
		const auto extractFront = [&](std::queue<HuffmanNode*>& queue)
		{
			HuffmanNode* front = queue.front();
			queue.pop();
			return front;
		};

		if(leafNodes.empty()) { return extractFront(parentNodes); }
		if (parentNodes.empty()) { return extractFront(leafNodes); }

		return leafNodes.front()->frequency < parentNodes.front()->frequency ?
			extractFront(leafNodes) : extractFront(parentNodes);
	};

	while(!leafNodes.empty() || parentNodes.size() > 1)
	{
		HuffmanNode *left {extractMin()}, *right {extractMin()};
		parentNodes.push(new HuffmanNode(0, left->frequency + right->frequency, left, right));
	}

	std::vector<HuffmanCode> codes;
	GetLeafCodes(codes, parentNodes.front(), {});
	return codes;
}

int main()
{
	// Reading the input.
	std::cout << "Reading input...\r";
	std::ifstream inputFile{ "../HuffmanCoding/Data.txt", std::ios::in };
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open the file!\n";
		return -1;
	}

	uint32_t symbolCount {0};
	inputFile >> symbolCount;

	std::vector<Data> data(symbolCount);

	Symbol symbol {0};
	for (Frequency frequency; inputFile >> frequency;)
	{
		data[symbol] = { symbol + 1, frequency };
		++symbol;
	}
	inputFile.close();

	const auto huffmanCodes = GetHuffmanCodes(data);

	size_t min {SIZE_MAX}, max {0};
	for (const auto& val : huffmanCodes | std::views::values)
	{
		const auto size = val.size();
		if (min > size) { min = size; }
		if (max < size) { max = size; }
	}

	std::cout << "Minimum code length: " << min << "\nMaximum code length: " << max << "\n";

	std::cin.get();
	return 0;
}
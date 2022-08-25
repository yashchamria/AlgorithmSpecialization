/******************************************************************************************
********** Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming *************
******************************************************************************************/

/********************* Needleman-Wunsch sequence alignment algorithm *********************/

#include <iostream>
#include <vector>

using Score = int;
using Sequence = std::string;

constexpr Score match = 5;
constexpr Score gap = -1;
constexpr Score mismatch = -2;
constexpr char blank = '_';

std::pair<Sequence, Sequence> GetOptimalSequences(const Sequence& lhs, const Sequence& rhs)
{
	std::vector memoizationSet(lhs.length() + 1, std::vector<Score>(rhs.length() + 1));

	// Initialing the zeroth values of the table.
	for (int i = 0; i < memoizationSet.size(); ++i) { memoizationSet[i][0] = i * gap; }
	for (int i = 0; i < memoizationSet[0].size(); ++i) { memoizationSet[0][i] = i * gap; }

	for (int i = 1; i < memoizationSet.size(); ++i)
	{
		for (int j = 1; j < memoizationSet[i].size(); ++j)
		{
			memoizationSet[i][j] = std::max(std::max(memoizationSet[i - 1][j], memoizationSet[i][j - 1]) + gap,
				memoizationSet[i - 1][j - 1] + (lhs[i - 1] == rhs[j - 1] ? match : mismatch));
		}
	}

	// Backtracking to find the optimal sequence.
	size_t i {lhs.length()}, j{rhs.length()};
	int const maxLength = i + j;
	Sequence seq1(maxLength, blank), seq2(maxLength, blank);
	int length = maxLength;

	while (i > 0 && j > 0)
	{
		const Score score = memoizationSet[i][j];

		if (score == memoizationSet[i - 1][j - 1] + (lhs[i - 1] == rhs[j - 1] ? match : mismatch))
		{
			seq1[--length] = lhs[--i];
			seq2[length] = rhs[--j];
		}
		else if (score == memoizationSet[i - 1][j] + gap)
		{
			seq1[--length] = lhs[--i];
		}
		else if (score == memoizationSet[i][j - 1] + gap)
		{
			seq2[--length] = rhs[--j];
		}
	}
	while (i > 0) { seq1[--length] = lhs[--i]; }
	while (j > 0) { seq2[--length] = rhs[--j]; }

	int initialBlanks {0};
	while (initialBlanks < maxLength && seq1[initialBlanks] == blank && seq2[initialBlanks] == blank) { ++initialBlanks; }

	return {seq1.substr(initialBlanks, maxLength - initialBlanks), seq2.substr(initialBlanks, maxLength - initialBlanks)};
}

int main()
{
	const Sequence lhs = "CGTGAATTCAT";
	const Sequence rhs = "GACTTAC";

	const auto optimalSequence = GetOptimalSequences(lhs, rhs);

	std::cout << "Input Sequence 1: " << lhs << "\n";
	std::cout << "Input Sequence 2: " << rhs << "\n";
	std::cout << "Optimal Sequence 1: " << optimalSequence.first << "\n";
	std::cout << "Optimal Sequence 2: " << optimalSequence.second << "\n";

	std::cin.get();
	return 0;
}
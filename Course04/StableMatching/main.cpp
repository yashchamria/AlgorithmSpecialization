/******************************************************************************************
******** Shortest Paths Revisited, NP-Complete Problems and What To Do About Them *********
******************************************************************************************/

/********************* Gale–Shapley Stable Matching Algorithm ****************************/

#include <iomanip>
#include <iostream>
#include <unordered_set>
#include <vector>

using Man = uint32_t;
using Woman = uint32_t;
using Matches = std::vector<Man>;

Matches GetStableMatches(const std::vector<std::vector<Woman>>& menPreferences, const std::vector<std::vector<Man>>& womenPreferences)
{
	Matches stableMatches(menPreferences.size(), 0);

	std::unordered_set<Man> freeMen;
	for (Man i = 1; i <= menPreferences.size(); ++i) { freeMen.insert(i); }

	while (!freeMen.empty())
	{
		for (const Man man = *freeMen.cbegin(); const auto & woman : menPreferences[man - 1])
		{
			if (stableMatches[woman - 1] == 0)
			{
				// New engagement.
				freeMen.erase(man);
				stableMatches[woman - 1] = man;
				break;
			}

			// Check for the re-engagement if the new man is more preferred.
			for (const auto& preferredMan : womenPreferences[woman - 1])
			{
				// if existing man is of higher preference.
				if (preferredMan == stableMatches[woman - 1]) { break; }

				if (preferredMan == man)
				{
					// Break the current engagement.
					freeMen.insert(stableMatches[woman - 1]);

					// New engagement.
					freeMen.erase(man);
					stableMatches[woman - 1] = man;
					break;
				}
			}

			if (!freeMen.contains(man)) { break; }
		}
	}

	return stableMatches;
}

int main()
{
	constexpr uint32_t numPairs = 8;

	const std::vector<std::vector<Woman>> menPreferences
	{
		{5, 7, 1, 2, 6, 8, 4, 3},  // <- 1
		{2, 3, 7, 5, 4, 1, 8, 6},  // <- 2
		{8, 5, 1, 4, 6, 2, 3, 7},  // <- 3
		{3, 2, 7, 4, 1, 6, 8, 5},  // <- 4
		{7, 2, 5, 1, 3, 6, 8, 4},  // <- 5
		{1, 6, 7, 5, 8, 4, 2, 3},  // <- 6
		{2, 5, 7, 8, 3, 4, 8, 1},  // <- 7
		{3, 8, 4, 5, 7, 2, 6, 1},  // <- 8
	};

	const std::vector<std::vector<Man>> womenPreferences
	{
		{5, 3, 7, 6, 1, 2, 8, 4},  // <- 1
		{8, 6, 3, 5, 7, 2, 1, 4},  // <- 2
		{1, 5, 6, 2, 4, 8, 7, 3},  // <- 3
		{8, 7, 3, 2, 4, 1, 5, 6},  // <- 4
		{6, 4, 7, 3, 8, 1, 2, 5},  // <- 5
		{2, 8, 5, 3, 4, 6, 7, 1},  // <- 6
		{7, 5, 2, 1, 8, 6, 4, 3},  // <- 7
		{7, 4, 1, 5, 2, 3, 6, 8},  // <- 8

	};

	const auto stableMatches = GetStableMatches(menPreferences, womenPreferences);

	std::cout << "Man    Woman    Local stability\n";
	for (Woman woman = 1; woman <= numPairs; ++woman)
	{
		const Man man = stableMatches[woman - 1];

		// Calculates the local stability score based on partner's ranking.
		float rank {0};
		for (const auto& preferredWoman : menPreferences[man - 1])
		{
			if (preferredWoman == woman) { break; }
			++rank;
		}
		for (const auto& preferredMan : womenPreferences[woman - 1])
		{
			if (preferredMan == man) { break; }
			++rank;
		}

		std::cout << " " << man << "       " << woman << "           " << std::setprecision(3) << 100.0f - rank * 50.0f / (numPairs - 1) << "\n";
	}

	std::cin.get();
	return 0;
}
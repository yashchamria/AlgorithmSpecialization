/******************************************************************************************
********** Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming *************
******************************************************************************************/

/********************************** Job Scheduler ****************************************/

#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using Priority = int;
using Time = int;
using Job = std::pair<Priority, Time>;

struct CompareJobByRatio
{
	bool operator()(const Job& job1, const Job& job2) const
	{
		const float score1 = (float)job1.first / (float)job1.second;
		const float score2 = (float)job2.first / (float)job2.second;

		return score1 > score2;
	}
};

struct CompareJobByDifference
{
	bool operator()(const Job& job1, const Job& job2) const
	{
		const int score1 = job1.first - job1.second;
		const int score2 = job2.first - job2.second;

		if(score1 == score2)
		{
			return job1.first > job2.first;
		}
		return score1 > score2;
	}
};

int main()
{
	// Reading the input.
	std::cout << "Reading input...\r";
	std::ifstream inputFile{ "../JobScheduler/JobsData.txt", std::ios::in };
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open the file!\n";
		return -1;
	}

	uint32_t jobCount {0};
	inputFile >> jobCount;

	std::vector<Job> jobs(jobCount);

	int index = 0;
	for (Job job; inputFile >> job.first >> job.second;)
	{
		jobs[index++] = job;
	}
	inputFile.close();

	const auto calculateScore = [&]
	{
		uint64_t completionTime{ 0 }, score{ 0 };
		for (const auto& job : jobs)
		{
			completionTime += job.second;
			score += completionTime * job.first;
		}
		return score;
	};

	std::ranges::sort(jobs, CompareJobByDifference());
	std::cout << "Completion cost by difference: " << calculateScore() << "\n";

	std::ranges::sort(jobs, CompareJobByRatio());
	std::cout << "Completion cost by ratio: " << calculateScore() << "\n";

	std::cin.get();
	return 0;
}
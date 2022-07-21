#include "PCH.h"
#include "Graphs/Graph.h"
#include "Graphs/MinCut.h"
#include "Sorting/Sort.h"
#include "Multiplication/Multiplication.h"

void MergeSort();
void QuickSort();
void KargerMinCut();
void KaratsubaMultiplication();

int main(int argc, char** argv)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    srand((unsigned int)time(nullptr));

    // KaratsubaMultiplication();
    // MergeSort();
    // QuickSort();
    KargerMinCut();

    std::cin.get();
    return 0;
}


void KaratsubaMultiplication()
{
    std::string lhs{}, rhs{};
    std::cout << "Multiply two integers of any size.\n";
    std::cout << "lhs: ";
    std::cin >> lhs;
    std::cout << "rhs: ";
    std::cin >> rhs;

    const auto start {std::chrono::high_resolution_clock::now()};

    std::cout << "Answer : " + Multiplication::KaratsubaMultiplication(lhs, rhs) + "\n\n";

    const auto end {std::chrono::high_resolution_clock::now()};
    std::cout << "Processing Time: " << (std::chrono::duration<float>)(end - start) << "\n";
}

void MergeSort()
{
    std::vector<int> input{};

    std::cout << "Reading file...\r";
    if (std::ifstream inputFile {"../source/Sorting/unsortedArray01.txt", std::ios::in}; inputFile.is_open())
    {
        int num{};
        while (inputFile >> num)
        {
            input.push_back(num);
        }
        inputFile.close();

    }
    else
    {
        std::cout << "Failed to open the file!\n";
    }

    if (!input.empty())
    {
        std::cout << "Sorting the array...\r";
        const auto start{std::chrono::high_resolution_clock::now()};
        Sort::MergeSort(&input[0], 0, (int)input.size() - 1);
        const auto end {std::chrono::high_resolution_clock::now()};

        std::cout << "Array sorted successfully.\n";
        std::cout << "Processing Time: " << (std::chrono::duration<float>)(end - start) << "\n";
        std::cout << "Outputting file...\r";

        if (std::fstream outputFile{ "../binaries/MergeSort.txt", std::ios::out }; outputFile.is_open())
        {
            for (const int number : input)
            {
                outputFile << number << "\n";
}
            outputFile.close();

            std::cout << "Output file saved -> binaries/MergeSort.txt\n";
        }
        else
        {
            std::cout << "Failed to save the output file!\n";
        }
    }
}

void QuickSort()
{
    std::vector<int> input{};

    std::cout << "Reading file...\r";
    if (std::ifstream inputFile{ "../source/Sorting/unsortedArray02.txt", std::ios::in }; inputFile.is_open())
    {
        int num{};
        while (inputFile >> num)
        {
            input.push_back(num);
        }
        inputFile.close();

    }
    else
    {
        std::cout << "Failed to open the file!\n";
    }

    if (!input.empty())
    {
        std::cout << "Sorting the array...\r";
        const auto start{ std::chrono::high_resolution_clock::now() };
        Sort::QuickSort(&input[0], 0, (int)input.size() - 1);
        const auto end{ std::chrono::high_resolution_clock::now() };

        std::cout << "Array sorted successfully.\n";
        std::cout << "Processing Time: " << (std::chrono::duration<float>)(end - start) << "\n";
        std::cout << "Outputting file...\r";

        if (std::fstream outputFile{ "../binaries/QuickSort.txt", std::ios::out }; outputFile.is_open())
        {
            for (const int number : input)
            {
                outputFile << number << "\n";
            }
            outputFile.close();

            std::cout << "Output file saved -> binaries/QuickSort.txt\n";
        }
        else
        {
            std::cout << "Failed to save the output file!\n";
        }
    }
}

void KargerMinCut()
{
    uint64_t vertices {};
    std::vector<Edge> edges {};

    std::cout << "Reading file...\r";
    if (std::ifstream inputFile{ "../source/Graphs/GraphData.txt", std::ios::in }; inputFile.is_open())
    {
        std::string line {};
        while (std::getline(inputFile, line))
        {
            std::istringstream lineStream {line};
            Vertex head = 0;
            lineStream >> head;
            ++vertices;

            Vertex tail = 0;
            while(lineStream >> tail)
            {
                if(tail > head)
                {
                    edges.emplace_back(Edge(head, tail));
                }
            }
        }
        inputFile.close();
        std::cout << "Processing Graph...\r";

        const auto start{ std::chrono::high_resolution_clock::now() };

        int minCut = MinCut::KargerMinCut({ vertices, edges }, vertices);
        std:: cout << "Karger Min Cut Count -> " << minCut << "\n";
        const auto end{ std::chrono::high_resolution_clock::now() };
    	std::cout << "Processing Time: " << (std::chrono::duration<float>)(end - start) << ", Iterations: " << vertices << "\n";

    }
    else
    {
        std::cout << "Failed to open the file!\n";
    }

}
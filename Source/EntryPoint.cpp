#include "PCH.h"
#include "Sorting/Sort.h"
#include "InversionCounting/Inversion.h"
#include "Multiplication/Multiplication.h"

void KaratsubaMultiplication_example();
void MergeSort_example();
void InversionCounting_example();

int main(int argc, char** argv)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //KaratsubaMultiplication_example();
    //MergeSort_example();
    InversionCounting_example();

    std::cin.get();
    return 0;
}


void KaratsubaMultiplication_example()
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

void MergeSort_example()
{
    std::vector<int> input{};

    std::cout << "Reading file...\r";
    if (std::ifstream inputFile {"../source/Sorting/unsortedArray.txt", std::ios::in}; inputFile.is_open())
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

        if (std::fstream outputFile{ "../binaries/sortedArray.txt", std::ios::out }; outputFile.is_open())
        {
            for (const int number : input)
            {
                outputFile << number << "\n";
}
            outputFile.close();

            std::cout << "Output file saved -> binaries/sortedArray.txt\n";
        }
        else
        {
            std::cout << "Failed to save the output file!\n";
        }
    }
}

void InversionCounting_example()
{
    std::vector<int> input{};

    std::cout << "Reading file...\r";
    if (std::ifstream inputFile{ "../source/InversionCounting/unsortedArray.txt", std::ios::in }; inputFile.is_open())
    {
        int num{};
        while (inputFile >> num)
        {
            input.push_back(num);
        }
        inputFile.close();

        if (!input.empty())
        {
            std::cout << "Counting the inversion...\r";
            const auto start  {std::chrono::high_resolution_clock::now()};
            const uint64_t pairCount = Inversion::InversionPairCount(&input[0], 0, (int)input.size() - 1);
            const auto end {std::chrono::high_resolution_clock::now()};

            std::cout << "Finished. Total inversion pair -> " << pairCount << "\n";
            std::cout << "Processing Time: " << (std::chrono::duration<float>)(end - start) << "\n";
        }
    }
    else
    {
        std::cout << "Failed to open the file!\n";
    }
}
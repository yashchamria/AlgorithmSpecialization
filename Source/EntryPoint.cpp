#include "PCH.h"
#include "Multiplication/Multiplication.h"

int main(int argc, char** argv)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    std::chrono::time_point<std::chrono::steady_clock> start {}, end {};

    ////////////////////////////////////////////////////////////
    ////////////// Karatsuba Multiplication ////////////////////
    ////////////////////////////////////////////////////////////

    std::string lhs {}, rhs {};
    std::cout << "Multiply two integers of any size.\n";
    std::cout << "lhs: ";
    std::cin >> lhs;
    std::cout << "rhs: ";
    std::cin >> rhs;

    start = std::chrono::high_resolution_clock::now();

    std::cout << "Answer : " + Multiplication::KaratsubaMultiplication(lhs, rhs) + "\n\n";

    end = std::chrono::high_resolution_clock::now();
    std::cout << "Processing Time: " << (std::chrono::duration<float>)(end - start) << "\n";

    return 0;
}
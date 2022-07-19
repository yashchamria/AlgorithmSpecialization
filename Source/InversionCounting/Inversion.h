#pragma once

class Inversion final
{
public:
    static uint64_t InversionPairCount(int array[], const int begin, const int end);

private:
    static uint64_t Count(int array[], const int start, const int mid, const int end);
};
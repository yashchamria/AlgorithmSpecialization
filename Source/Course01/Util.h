#pragma once

template<typename T>
void Swap(T& lhs, T& rhs)
{
    const int temp = lhs;
    lhs = rhs;
    rhs = temp;
}
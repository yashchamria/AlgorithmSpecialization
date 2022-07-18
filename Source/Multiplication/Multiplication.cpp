#include "PCH.h"
#include "Multiplication.h"

std::string Multiplication::KaratsubaMultiplication(std::string& lhs, std::string& rhs)
{
    if (lhs.empty() || rhs.empty())
    {
        return "0";
    }

    bool isNegative {};
    if (lhs[0] == '-' && rhs[0] != '-')
    {
        lhs = lhs.substr(1, lhs.size() - 1);
        isNegative = true;
    }
    else if (rhs[0] == '-' && lhs[0] != '-')
    {
        rhs = rhs.substr(1, rhs.size() - 1);
        isNegative = true;
    }
    else if (lhs[0] == '-' && rhs[0] == '-')
    {
        lhs = lhs.substr(1, lhs.size() - 1);
        rhs = rhs.substr(1, rhs.size() - 1);
        isNegative = false;
    }
    else
    {
        isNegative = false;
    }

    std::string result = KaratsubaMultiplication_Internal(lhs, rhs);
    result.erase(0, std::min(result.find_first_not_of('0'), result.size() - 1));

    if (isNegative)
    {
        result = "-" + result;
    }

    return result;
}

std::string Multiplication::KaratsubaMultiplication_Internal(std::string& lhs, std::string& rhs)
{
    MakeEqualLength(lhs, rhs);

    const size_t size = lhs.size();
    const size_t halfSize = size / 2;

    if (size < 2)
    {
        return std::to_string(ToInt(lhs[0]) * ToInt(rhs[0]));
    }

    std::string lhs1 = lhs.substr(0, halfSize);
    std::string lhs2 = lhs.substr(halfSize, size - halfSize);
    std::string rhs1 = rhs.substr(0, halfSize);
    std::string rhs2 = rhs.substr(halfSize, size - halfSize);

    std::string k1 = KaratsubaMultiplication_Internal(lhs1, rhs1);
    std::string k2 = KaratsubaMultiplication_Internal(lhs2, rhs2);

    std::string lhs12 = Add(lhs1, lhs2);
    std::string rhs12 = Add(rhs1, rhs2);
    std::string k3 = KaratsubaMultiplication_Internal(lhs12, rhs12);

    std::string k12 = Add(k1, k2);
    k3 = Subtract(k3, k12);

    for (int i = 0; i < 2 * (size - halfSize); i++)
    {
        k1.append("0");

        if (i % 2 == 0)
        {
            k3.append("0");
        }
    }

	std::string k23 = Add(k2, k3);
    return Add(k1,k23);
}

std::string Multiplication::Add(std::string& lhs, std::string& rhs)
{
    MakeEqualLength(lhs, rhs);

    const size_t size = lhs.size();

    if (size < 2)
    {
        return std::to_string(ToInt(lhs[0]) + ToInt(rhs[0]));
    }

    std::string result {};
    int carry {0};

    for (int i = (int)size - 1; i > -1; i--)
    {
        std::string digitSum = std::to_string(ToInt(lhs[i]) + ToInt(rhs[i]) + carry);

        if (digitSum.size() > 1)
        {
            carry = ToInt(digitSum[0]);
            digitSum = digitSum[1];
        }
        else
        {
            carry = 0;
        }

        result.insert(0, digitSum);
    }

    if (carry)
    {
        result = std::to_string(carry) + result;
    }

    return result;
}

std::string Multiplication::Subtract(std::string& lhs, std::string& rhs)
{
    MakeEqualLength(lhs, rhs);
    const size_t size = lhs.size();

    if (size < 2)
    {
        return std::to_string(ToInt(lhs[0]) - ToInt(rhs[0]));
    }

    std::string result {};

    for (int i = (int)size - 1; i > -1; i--)
    {
        const int diff = ToInt(lhs[i]) - ToInt(rhs[i]);

        if (diff >= 0)
        {
            result.insert(0, std::to_string(diff));
        }
        else
        {
            result.insert(0, std::to_string(diff + 10));

            for (int j = i - 1; j > -1; j--)
            {
                if (ToInt(lhs[j]) > 0)
                {
                    lhs[j]--;
                    break;
                }

            	lhs[j] = '9';
            }
        }
    }

    return result;
}

void Multiplication::MakeEqualLength(std::string& lhs, std::string& rhs)
{
	if (const int diff = (int)lhs.size() - (int)rhs.size(); diff < 0)
    {
        lhs = std::string(-diff, '0') + lhs;
    }
    else if (diff > 0)
    {
        rhs = std::string(diff, '0') + rhs;
    }
}
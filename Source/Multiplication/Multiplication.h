class Multiplication
{
public:
    static std::string KaratsubaMultiplication(std::string& lhs, std::string& rhs);

private:
    static std::string KaratsubaMultiplication_Internal(std::string& lhs, std::string& rhs);

private:
    static std::string Add(std::string& lhs, std::string& rhs);
    static std::string Subtract(std::string& lhs, std::string& rhs);

private:
    static int ToInt(const char& value) { return value - '0'; }
    static void MakeEqualLength(std::string& lhs, std::string& rhs);
};
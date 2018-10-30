#include <string>

class Caculator
{
public:
    Caculator();

    int caculate(std::string expr, int &res);
    std::string caculate(std::string expr);

    void toBinary(int decimal, std::string &binary);
    void toOctal(int decimal, std::string &octal);
    void toHexadecimal(int decimal, std::string &hexa);
    void toDecimal(int &decimal, std::string &str);

    void bToDecimal(std::string &binary, int &decimal);
    void oToDecimal(std::string &octal, int &decimal);
    void hexaToDecimal(std::string &hexa, int &decimal);

private:
    void removeSpace(std::string &str);
    void split(std::string &str, std::string &substr_1, std::string &substr_2, const std::string &delimeter);
};

#include "Caculator.h"
#include <iostream>
#include <algorithm>
#include <math.h>

Caculator::Caculator() {}

std::string Caculator::caculate(std::string expr)
{
    int res = 0;
    try{
        if (caculate(expr, res) == -1) {
            return  "0 cannot be devided";
        }
    }
    catch(std::exception e) {
        return "overflow";
    }

    std::string str_b, str_o, str_x;
    toBinary(res, str_b);
    toOctal(res, str_o);
    toHexadecimal(res, str_x);

    return std::to_string(res) + "  " + str_b + "   " + str_o + "   " + str_x;
}

int Caculator::caculate(std::string expr, int &res)
{
    int operand_1 = 0, operand_2 = 0;
    std::string substr_1, substr_2;
    if (expr.find("+") != std::string::npos) {
        split(expr, substr_1, substr_2, "+");
        toDecimal(operand_1, substr_1);
        toDecimal(operand_2, substr_2);
        res = operand_1 + operand_2;
        if(res < operand_1 || res < operand_2)
            throw std::exception();
    }  else if (expr.find("-") != std::string::npos) {
        split(expr, substr_1, substr_2, "-");
        toDecimal(operand_1, substr_1);
        toDecimal(operand_2, substr_2);
        res = operand_1 - operand_2;
        if(res > operand_1)
            throw std::exception();
    } else if (expr.find("*") != std::string::npos) {
        split(expr, substr_1, substr_2, "*");
        toDecimal(operand_1, substr_1);
        toDecimal(operand_2, substr_2);
        res = operand_1 * operand_2;
        if (log2(operand_1) + log2(operand_2) >= 32)
            throw std::exception();
    } else if (expr.find("/") != std::string::npos) {
        split(expr, substr_1, substr_2, "/");
        toDecimal(operand_1, substr_1);
        toDecimal(operand_2, substr_2);
        if (operand_2 == 0) { std::cout << "0 cannot be devided\n"; return -1; }
        res = operand_1 / operand_2;
     } else {
        // for other operators
    }
    return 0;
}

void Caculator::toBinary(int decimal, std::string &binary)
{
    while(decimal > 0) {
        binary = std::to_string(decimal % 2) + binary;
        decimal = decimal / 2;
    }
    binary = "b" + binary;
}

void Caculator::toOctal(int decimal, std::string &octal)
{
    while(decimal > 0) {
        octal = std::to_string(decimal % 8) + octal;
        decimal = decimal / 8;
    }
    octal = "o" + octal;
}

void Caculator::toHexadecimal(int decimal, std::string &hexa)
{
    while(decimal > 0) {
        switch (decimal%16) {
        std::cout << "ecimal%16: " << decimal%16 << "\n";
        case 15:
            hexa = "F" + hexa;
            break;
        case 14:
            hexa = "E" + hexa;
            break;
        case 13:
            hexa = "D" + hexa;
            break;
        case 12:
            hexa = "C" + hexa;
            break;
        case 11:
            hexa = "B" + hexa;
            break;
        case 10:
            hexa = "A" + hexa;
            break;
        default:
            hexa = std::to_string(decimal % 16) + hexa;
            break;
        }

        decimal = decimal / 16;
    }

    hexa = "0x" + hexa;
}

void Caculator::toDecimal(int &decimal, std::string &str)
{
    if (str.find("0x") != std::string::npos || str.find("0X") != std::string::npos) {
       hexaToDecimal(str, decimal);
       return;
    }
    switch (str.at(0)) {
        case 'b':
            bToDecimal(str, decimal);
            break;
        case 'o':
            oToDecimal(str, decimal);
            break;
        default:
            decimal = std::stoi(str);
            break;
    }
}

void Caculator::bToDecimal(std::string &binary, int &decimal)
{
    int len = binary.length();
    for (int i = 1; i < len; i++) {
         decimal += std::stoi(binary.substr(i, 1)) * pow(2, len-i-1);
    }
}

void Caculator::oToDecimal(std::string &octal, int &decimal)
{
    int len = octal.length();
    for (int i = 1; i < len; i++) {
         decimal += std::stoi(octal.substr(i, 1)) * pow(8, len-i-1);
    }
}

void Caculator::hexaToDecimal(std::string &hexa, int &decimal)
{
    int len = hexa.length();
    for (int i = 2; i <len; i++) {
        switch (hexa.at(i)) {
            case 'A':
            case 'a':
                decimal += 10 * pow(16, len-i-1);
                break;
            case 'B':
            case 'b':
                decimal += 11 * pow(16, len-i-1);
                break;
            case 'C':
            case 'c':
                decimal += 12 * pow(16, len-i-1);
                break;
            case 'D':
            case 'd':
                decimal += 13 * pow(16, len-i-1);
                break;
            case 'E':
            case 'e':
                decimal += 14 * pow(16, len-i-1);
                break;
            case 'F':
            case 'f':
                decimal += 15 * pow(16, len-i-1);
                break ;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                decimal += std::stoi(hexa.substr(i, 1)) * pow(16, len-i-1);
                break;
            default:

                break;
        }
    }
}

void Caculator::removeSpace(std::string &str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

void Caculator::split(std::string &str, std::string &substr_1, std::string &substr_2, const std::string &delimeter)
{
    int pos = str.find(delimeter);
    substr_1 = str.substr(0, pos);
    removeSpace(substr_1);   // remove white Space
    str.erase(0, pos+1);    // '+' has length 1
    substr_2 = str;
    removeSpace(substr_2);      // remove white Space
}

#include "numconverter.h"
#include <utility>
#include <vector>
#include <string>

std::string NumConverter::toRoman(unsigned arabic)
{
    const std::vector<std::pair<unsigned,std::string>> table{
    {1000u, "M"},
    {900u, "CM"},
    {500u, "D"},
    {400u, "CD"},
    {100u, "C"},
    {90u, "XC"},
    {50u, "L"},
    {40u, "XL"},
    {10u, "X"},
    {9u, "IX"},
    {5u, "V"},
    {4u, "IV"},
    {1u, "I"}
    };

    std::string roman;
    for (auto& pair: table)
    {
        while (pair.first <= arabic)
        {
            arabic -= pair.first;
            roman += pair.second;
        }
    }
    return roman;
}

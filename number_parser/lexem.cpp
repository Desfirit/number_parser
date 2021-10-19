#include "lexem.h"
#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include <QDebug>
#include <iomanip>

size_t Lexem::compare(const std::string &s1,const std::string &s2) const
{
    size_t similarity = 0;
    if(s1.size() == s2.size())
        similarity += 10;


    std::string* p1 (&(const_cast<std::string&>(s1)));
    std::string* p2 (&(const_cast<std::string&>(s2)));
    if(p1->size() > p2->size())
        swap(p1,p2);

    return std::inner_product(begin(*p1), end(*p1), begin(*p2), similarity, std::plus<size_t>{}, [](char& a, char& b){
        if(a == b)
            return 5;
        else
            return 0;
    });
}

void Lexem::read(std::string& str)
{
    const std::map<std::string,LexemType> mger{
        {"un",UNIT}, {"deux", UNIT},{"trois",UNIT}, {"quatre", UNIT},
        {"cinq",UNIT}, {"six", UNIT},{"sept",UNIT}, {"huit", UNIT},
        {"neuf",UNIT},

        {"dix", MGER},{"onze",MGER},
        {"douze", MGER},{"treize",MGER},
        {"quatorze", MGER},{"quinze",MGER},
        {"seize", MGER},{"dix-sept",MGER},
        {"dix-huint", MGER},{"dix-neuf", MGER},

        {"vingt", TWENTY},
        {"soixante", SIXTY},

        {"trente", DOZEN}, {"quarante", DOZEN},
        {"cinquante", DOZEN},

        {"cent", HUNDRED},
    };

    auto foundedType = mger.find(str);
    if(foundedType == end(mger))
    {
        std::string mostSimiliar;
        size_t maxSimilarity = 0;
        for(auto& [val, type] : mger)
        {
            if(auto similarity(compare(str,val)); similarity > maxSimilarity)
            {
                maxSimilarity = similarity;
                mostSimiliar = val;
            }
        }

        if(maxSimilarity >= 15)
            throw ("Лексическая ошибка в слове: \"" + str + "\", возможно вы имели в виду " + mostSimiliar);
        else
            throw ("Лексическая ошибка в слове: \"" + str + "\"");
    }

    type = foundedType->second;
    val = str;
}

std::istream& operator>>(std::istream& is, Lexem& lex)
{
    std::string val;
    if(is >> val)
        lex.read(val);
    return is;
}

#include "parser.h"
#include <vector>
#include "lexem.h"
#include <map>
#include <functional>
#include <string>
#include <QDebug>

int Parser::parse_hundred()
{
    const int curVal = 100;
    auto prevLex = curLex++;
    curLevel = std::min(100,curLevel);

    if(curLex == endLex)
        return curVal;

    const std::map<LexemType,std::function<int(void)>> mgers{
        {DOZEN, [&](){
        return curVal + parse_dozens();
        }},
        {SIXTY, [&](){
        return curVal + parse_sixty();
        }},
        {TWENTY, [&](){
        return curVal + parse_twenty();
        }},
        {MGER, [&](){
        return curVal + parse_mger();
        }},
        {UNIT, [&](){
        return curVal + parse_units();
        }},
    };
    auto founded = mgers.find(curLex->type);
    if(founded == end(mgers))
        throw std::pair{prevLex->type, curLex->type};

    return founded->second();
}


int Parser::parse_dozens()
{
    const std::map<std::string,int> dozens{
        {"trente", 30}, {"quarante", 40},
        {"cinquante", 50},
    };

    auto prevLex = curLex++;
    curLevel = std::min(10,curLevel);
    int curVal = dozens.find((prevLex)->val)->second;

    if(curLex == endLex)
        return curVal;

    const std::map<LexemType,std::function<int(void)>> mgers{
        {UNIT, [&](){
        return curVal + parse_units();
        }},
    };
    auto founded = mgers.find(curLex->type);
    if(founded == end(mgers))
        throw std::pair{prevLex->type, curLex->type};

    return founded->second();
}


int Parser::parse_sixty()
{
    const int curVal = 60;
    auto prevLex = curLex++;
    curLevel = std::min(10,curLevel);
    if(curLex == endLex)
        return curVal;

    const std::map<LexemType,std::function<int(void)>> mgers{
        {MGER, [&](){
        return curVal + parse_mger();
        }},
        {UNIT, [&](){
        return curVal + parse_units();
        }},
    };
    auto founded = mgers.find(curLex->type);
    if(founded == end(mgers))
        throw std::pair{prevLex->type, curLex->type};

    return founded->second();
}


int Parser::parse_twenty()
{

    const int curVal = 20;

    auto prevLex = curLex++;
    curLevel = std::min(10,curLevel);
    if(curLex == endLex)
        return curVal;

    const std::map<LexemType,std::function<int(void)>> mgers{
        {UNIT, [&](){
        return curVal + parse_units();
        }},
        {MGER, [&](){
        return curVal + parse_mger();
        }},
    };

    auto founded = mgers.find(curLex->type);
    if(founded == end(mgers))
        throw std::pair{prevLex->type, curLex->type};

    return founded->second();
}


int Parser::parse_mger()
{
    const std::map<std::string,int> dozens{
        {"dix", 10},{"onze",11},
        {"douze", 12},{"treize",13},
        {"quatorze", 14},{"quinze",15},
        {"seize", 16},{"dix-sept",17},
        {"dix-huint", 18},{"dix-neuf", 19},
    };

    auto prevLex = curLex++;
    curLevel = std::min(10,curLevel);
    int curVal = dozens.find((prevLex)->val)->second;

    if(curLex != endLex)
        throw std::pair{prevLex->type, curLex->type};
    return curVal;
}


int Parser::parse_units()
{
    const std::map<std::string,int> dozens{
        {"un",1}, {"deux", 2},{"trois",3}, {"quatre", 4},
        {"cinq",5}, {"six", 6},{"sept",7}, {"huit", 8},
        {"neuf",9},
    };

    auto prevLex = curLex++;
    int curVal = dozens.find((prevLex)->val)->second;

    if(curLex == endLex)
        return curVal;

    const std::map<LexemType,std::function<int(void)>> mgers{
        {HUNDRED, [&](){
        if(curLevel <= 100)
            throw std::pair{prevLex->type, curLex->type};
        return curVal * 100 + parse_hundred() - 100;
        }},
        {TWENTY, [&](){
        if(curLevel <= 20)
            throw std::pair{prevLex->type, curLex->type};
        return curVal * 20 + parse_twenty() - 20;
        }},
    };
    auto founded = mgers.find(curLex->type);
    if(founded == end(mgers))
        throw std::pair{prevLex->type, curLex->type};

    return founded->second();
}


int Parser::parse(std::vector<Lexem>& lexems)
{
    const std::map<LexemType,std::function<int(void)>> parsers{
        {UNIT, [&](){
        return parse_units();
        }},
        {MGER, [&](){
        return parse_mger();
        }},
        {TWENTY, [&](){
        return parse_twenty();
        }},
        {SIXTY, [&](){
        return parse_sixty();
        }},
        {HUNDRED, [&](){
        return parse_hundred();
        }},
    };
    curLex = begin(lexems);
    endLex = end(lexems);
    curLevel = 1000;
    return parsers.find(curLex->type)->second();
}

int Parser::parse(std::vector<Lexem>::iterator beg, std::vector<Lexem>::iterator end)
{
    const std::map<LexemType,std::function<int(void)>> parsers{
        {UNIT, [&](){
        return parse_units();
        }},
        {MGER, [&](){
        return parse_mger();
        }},
        {TWENTY, [&](){
        return parse_twenty();
        }},
        {SIXTY, [&](){
        return parse_sixty();
        }},
        {HUNDRED, [&](){
        return parse_hundred();
        }},
    };
    curLex = beg;
    endLex = end;
    curLevel = 1000;
    return parsers.find(curLex->type)->second();
}

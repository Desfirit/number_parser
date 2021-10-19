#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "lexem.h"

class Parser
{
    static inline std::vector<Lexem>::iterator curLex;
    static inline std::vector<Lexem>::iterator endLex;
    static inline int curLevel;

    static int parse_hundred();
    static int parse_dozens();
    static int parse_sixty();
    static int parse_twenty();
    static int parse_mger();
    static int parse_units();


public:
    //Parser(std::vector<Lexem> lexems): curLex(begin(lexems)), endLex(end(lexems)), lexems(lexems) {}
    //Parser(std::vector<Lexem>::iterator beg, std::vector<Lexem>::iterator end): curLex{beg}, endLex{end}{}

    static int parse(std::vector<Lexem>& lexems);
    static int parse(std::vector<Lexem>::iterator beg, std::vector<Lexem>::iterator end);
};

#endif // PARSER_H

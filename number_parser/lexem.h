#ifndef LEXEM_H
#define LEXEM_H
#include <string>

enum LexemType
{
    UNIT,
    MGER, //11-19
    TWENTY,
    SIXTY,
    DOZEN,
    HUNDRED,
};

class Lexem
{
public:
    LexemType type;
    std::string val;

    size_t compare(const std::string &s1,const std::string &s2) const;
    void read(std::string& str);
};

std::istream& operator>>(std::istream& is, Lexem& lex);

#endif // LEXEM_H

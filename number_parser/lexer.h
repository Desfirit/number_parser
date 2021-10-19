#ifndef LEXER_H
#define LEXER_H


#include <vector>
#include <string>
#include "lexem.h"


class Lexer
{
public:

    static std::vector<Lexem> read(std::string& str);
};

#endif // LEXER_H

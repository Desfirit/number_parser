#include "lexer.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "lexem.h"

using namespace std;

vector<Lexem> Lexer::read(string& str)
{
    istringstream ss(str);
    vector<Lexem> res;
    copy(istream_iterator<Lexem>{ss}, {}, back_inserter(res));
    return res;
}



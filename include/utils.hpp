#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <iostream>
#include <sstream>
#include <fstream>

#include <cstring>
#include <vector>
#include <regex>
#include <map>

using namespace std;

struct var {
    string name;
    double val;
};

//Influenced by "numexpr"
double opPrior2();
double opPrior1();
double _Number();

//Misc
void _print();
void decl();
double expr();
void assign();
bool comparison();
void block();

//Statements
void statement();
void if_st();
void for_st();

//Utilities
vector<string> FileToTokens(char *file_name);
int match(string *tokens, const string& str);

#endif
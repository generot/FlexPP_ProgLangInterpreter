#include "../include/utils.hpp"

vector<string> FileToTokens(char *file_name) {
    ifstream file;
    file.open(file_name, ios::in);
    
    stringstream strm;
    strm << file.rdbuf();

    string str = strm.str();

    vector<string> token_vec;
    char *token = strtok((char*)str.c_str(), " \t\n");

    do {
        token_vec.push_back(string(token));
        token = strtok(nullptr, " \t\n");
    } while(token);

    return token_vec;
}
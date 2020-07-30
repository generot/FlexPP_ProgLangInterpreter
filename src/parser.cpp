#include "../include/utils.hpp"

string compOpers[] = {"<=", ">=", "<", ">", "==", "!="};
regex rg("[a-zA-Z]+");

char *numexpr;

string _stdout, *tokens, *initMem;
stringstream sm;
map<string, var> mem;

int match(string *tokens, const string& str) {
    string *initPos = tokens;
    while(tokens) {
        if(*tokens == str)
            return (int)(tokens - initPos);
        tokens++;
    }
    return 0;
}

void block() {
    if(*tokens == "begin") {
        tokens++;
        while((*tokens).c_str()) {
            decl();
            statement();
            _print();

            tokens++;

            if(*tokens == "end")
                break;
        }
    }
}

void statement() {
    if(*(tokens+1) == "=")
        assign();
    else if(*tokens == "if:")
        if_st();
    else if(*tokens == "while:")
        for_st();
}

void for_st() {
    bool comp;
    string *ptr = tokens;

    do {
        if(*tokens == "while:") {
            tokens++;
            comp = comparison();
            tokens++;

            block();
            tokens = ptr;
        } else break;
    } while(comp);

    if(!comp) tokens += match(tokens, "end");
}

void if_st() {
    bool compRes; 
    if(*tokens == "if:") {
        tokens++;
        compRes = comparison();
        tokens++;

        if(compRes) block();
        else tokens += match(tokens, "end");
    }
}

void _print() {
    if(*tokens == "print") {
        tokens++;

        double ret = expr();
        sm << ret;
    } else if(*tokens == "printc") {
        tokens++;

        double ret = expr();
        sm << (char)ret;
    }

    if(*(tokens+1) == "eol") {
        sm << std::endl;
    }
}

double expr() {
    bool isNumExp = false;

    for(string::iterator i = (*tokens).begin(); i < (*tokens).end(); i++) {
        isNumExp = (*i >= '0' && *i <= '9') || *i == '+' || *i == '-'|| 
            *i == '*' || *i == '/' || *i == ')' || *i == '(';
        if(isNumExp) break;
    }

    //Really hacky way of determining whether an expression is a character
    if((*tokens)[0] == '\'' && (*tokens)[2] == '\'')
        return (*tokens)[1];

    //If an expression contains any numeric symbols, operators(+,-,/,*) or parentheses
    //opPrior2() will be called, which is the parser for numerical expressions
    if(isNumExp) {
        string tkn = string(*tokens), modTkn = tkn;
        numexpr = (char*)(*tokens).c_str();
        
        smatch abcd;
        while(regex_search(tkn, abcd, rg)) {
            regex newRg(abcd[0].str());
            std::stringstream strm;

            strm << mem[abcd[0].str()].val;

            modTkn = regex_replace(modTkn, newRg, strm.str()).c_str();
            tkn = abcd.suffix().str();
        }

        numexpr = (char*)modTkn.c_str();
        return opPrior2();
    } else return mem[string(*tokens)].val;
}

bool comparison() {
    double var1 = expr();

    tokens++;
    string tkn = *tokens;
    tokens++;

    double var2 = expr();

    for(size_t i = 0; i < sizeof(compOpers)/sizeof(string*); i++) {
        if(tkn == compOpers[i]) {
            switch(i) {
            case 0: return var1 <= var2; break;
            case 1: return var1 >= var2; break;
            case 2: return var1 < var2; break;
            case 3: return var1 > var2; break;
            case 4: return var1 == var2; break;
            case 5: return var1 != var2; break;
            }
        }
    }

    return false;
}

void assign() {
        string name = *tokens;

        tokens++;
        if(*tokens == "=") {
            tokens++;

            var newVar = {name, expr()};
            mem[name] = newVar;
        }
}

void decl() {
    if(*tokens == "set") {
        tokens++;

        var newVar = {*tokens, 0};
        mem[newVar.name] = newVar;
 
        if((*(tokens+1)).c_str())
            assign();
    }
}

double opPrior2() {
    double fnum = opPrior1();
    while(*numexpr == '+' || *numexpr == '-') {
        char prevChar = *numexpr;

        numexpr++;
        double snum = opPrior1();

        prevChar == '+' ? fnum += snum : prevChar == '-' ? fnum -= snum : 0;
    }
    return fnum;
}

double opPrior1() {
    double fnum = _Number();
    while(*numexpr == '*' || *numexpr == '/') {
        char prevChar = *numexpr;

        numexpr++;
        double snum = _Number();

        prevChar == '*' ? fnum *= snum : prevChar == '/' ? fnum /= snum : 0;
    }
    return fnum;
}

double _Number() {
    double res = 0;
    while(*numexpr >= '0' && *numexpr <= '9') {
        res = res * 10 + (*numexpr - '0');
        numexpr++;
    }

    if(*numexpr == '(') {
        numexpr++;
        res = opPrior2();
        if(*numexpr == ')')
            numexpr++;
    }
    return res;
}

int main(int argc, char **argv) {
    vector<string> tkns = FileToTokens(argv[1]);
    int index = 0;

    tokens = new string[tkns.size()];
    initMem = tokens;

    for(string tkn : tkns)
        tokens[index++] = tkn;

    block();
    _stdout = !sm.str().empty() ? sm.str() : "STDOUT is empty";
    cout << _stdout;

    delete[] initMem;
    return EXIT_SUCCESS;
}
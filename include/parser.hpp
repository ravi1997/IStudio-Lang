#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include<types.hpp>
#include<terminal.hpp>
#include<nonterminal.hpp>
class FileNotFound{};

class Parser{
    ifstream file;
    vector<string> options;
public:
    Parser(string f,vector<string> o):file{f},options{o}{
        if(!file.good())
            throw FileNotFound{};
    }
    ~Parser(){
        file.close();
    }
    
    
};

#endif
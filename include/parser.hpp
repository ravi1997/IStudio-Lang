#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include<types.hpp>
#include<terminal.hpp>
#include<nonterminal.hpp>
class FileNotFound{};

template<typename Option,typename t=void>
class Parser{
    ifstream file;
    vector<string> options;
    Option option;
public:
    Parser(string f,vector<string> o):file{f},options{o},option{options}{
        if(!file.good())
            throw FileNotFound{};
    }
    ~Parser(){
        file.close();
    }
    void setGrammar(){
        
    }
    Option& getOption(){
        return option;
    }
    
};

#endif
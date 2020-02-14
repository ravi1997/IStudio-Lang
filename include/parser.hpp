#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#ifndef _GRAMMMAR_HPP_
#include<grammar.hpp>
#endif

#include<options.hpp>

class FileNotFound{};

template<typename t=void>
class Parser{
    ifstream file;
    vector<string> options;
    Options option;
    Grammar<t> g;
public:
    Parser(string f,vector<string> o):file{f},options{o},option{options}{
        if(!file.good())
            throw FileNotFound{};
    }
    ~Parser(){
        file.close();
    }
    void setGrammar(Grammar<t> e){
        g=e;
    }
    void init(){
        
    }
    Options& getOption(){
        return option;
    }
    
};

#endif
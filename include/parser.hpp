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
    string code;
    
    enum class Type{
        LL0,
        LR0
    };
    Type parserType;
    union ParserTable{
        map<NonTerminal<t>,map<Terminal,Rule<t>>> LL0Table;
        struct LR0{
            enum class Type{
                SHIFT,
                REDUCE
            };
            map<int,map<Terminal,pair<Type,int>>> actionTable;
            map<int,map<NonTerminal<t>,int>> gotoTable;
        }LR0Table;
        ~ParserTable(){}
        ParserTable(){}
    }parseTable;
    
    
public:
    Parser(string f,vector<string> o,string s="LL0"):file{f},options{o},option{options}{
        if(!file.good())
            throw FileNotFound{};
        char c;
        while(file>>noskipws>>c)
            code+=c;
        if(s=="LL0")
            parserType=LL0;
        else
            parserType=LR0;
        //cout<<code<<endl;
    }
    ~Parser(){
        file.close();
    }
    void setGrammar(Grammar<t> e){
        g=e;
    }
    void init(){
        if(parserType==Type::LL0){
            for(auto 
            parserTable.LL0Table[]
        }
        else{
        
        }
    }
    Token getNextToken(){
        return g.getNextToken();
    }
    void startParsing(){

    }
    Options& getOption(){
        return option;
    }

};

#endif

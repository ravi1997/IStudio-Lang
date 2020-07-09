#ifndef _PARSER_HPP_
#define _PARSER_HPP_ 1

#ifndef _OPTIONS_HPP_
#include <options.hpp>
#endif // !_OPTIONS_HPP_

#ifndef _LOGGER_HPP_
#include<logger.hpp>
#endif // !_LOGGER_HPP_

#ifndef _GRAMMAR_HPP_
#include <grammar.hpp>
#endif // !_Grammar_HPP_

#ifndef _HANDLE_RULE_HPP_
#include <handlerule.hpp>
#endif

        enum class ParserType
        {
            LL1,
            SLR,
            CLR
        };
        Logger &operator<<(Logger &o, ParserType p)
        {
            switch (p)
            {
            case ParserType::LL1:
                o << "LL1";
                break;
            case ParserType::SLR:
                o << "SLR";
                break;
            case ParserType::CLR:
                o << "CLR";
                break;
            }
            return o;
        }
template<typename t>
class Parser{
    public:



    private:
    mutable string code = "";
    mutable unsigned int line = 0;
    const string fileName;
    const Options options;
    vector<Terminal<t>> skipTerminals;
    Grammar<t> grammar;


    const ParserType parserType;
    variant<LL1Parser<t>, SLRParser<t>,CLRParser<t>> table;

public:
    Parser(string f, Grammar<t> gg, vector<string> o, vector<Terminal<t>> ng, ParserType s=ParserType::CLR) : fileName{f}, options{o}, grammar{gg}, parserType{s}{
        Logger lg;
        auto x = options.getLogger();
        if (x)
            lg = options.getLoggerFile();

        if (x)
            lg << "Parsing started for : " << fileName << Logger::endl;

        ifstream file(fileName);
        if (!file.good())
            throw FileNotFound{};

        if (x)
            lg << "File Opened Successfully : " << fileName << Logger::endl;

        if (x)
            lg << "File character read : started" << Logger::endl;
        char c;
        while (file >> noskipws >> c)
            code += c;

        if (x)
            lg << "File character read : successfull" << Logger::endl;

        if (x)
            lg << "Skip Character read : started" << Logger::endl;

        for (auto st : ng)
            skipTerminals.push_back(st);

        if (x)
            lg << "Skip Character read : successfull" << Logger::endl;

        if (x)
            lg << "Parser Type : " << s << Logger::endl;
    }


    void init(){
        Logger lg;
        auto x = options.getLogger();
        if (x)
            lg = options.getLoggerFile();
        
        if(x)
            lg<<"Parsing Setting : started "<<Logger::endl;
        
        if(parserType==ParserType::CLR){
            CLRAction<t> a;
            CLRGoto<t> g;
            CLRState<t> I;
            Grammar<t> augmented=grammar.getAugmented();
            if (x)
                lg << "Augmented Grammer :" << Logger::endl<<augmented;

            NonTerminal<t> Start=augmented.getStart();
            I=(*Start.rules)[0].getHandleRule().getState(augmented,LookAheads<t>{Terminal<int>::DOLLAR});
            
            vector<CLRState<t>> states;

            vector<pair<CLRState<t>, NonTerminal<t>>> gotoList;
            vector<pair<CLRState<t>, variant<Terminal<t>, UnaryPre<t>, UnaryPost<t>, Binary<t>>>> actionList;
            do{
                if(find(states.begin(),states.end(),I)!=states.end())
                    continue;
                states.push_back(I);
                for(auto i:getGoto(I))
                    gotoList.push_back(pair{I,i});

                for (auto i : getAction(I))
                    actionList.push_back(pair{I, i});

                if(gotoList.size()>0){
                    auto [x,y]=gotoList.back();
                    gotoList.pop_back();
                    I=nextState(augmented,x,y);
                    g[x][y]=(find(states.begin(),states.end(),x)!=states.end())?distance(states.begin(),find(states.begin(),states.end(),x)):states.size();
                }
                else if(actionList.size()>0){
                    auto [x,y]=actionList.back();
                    actionList.pop_back();
                    I = nextState(augmented,x, y);
                    a[x][y] = pair{getSR(I),(find(states.begin(), states.end(), x) != states.end()) ? distance(states.begin(), find(states.begin(), states.end(), x)) : states.size()};
                }

            }while(gotoList.size()>0 || actionList.size()>0);

            table = CLRParser<t>{a,g};
        }
        else{}

        if (x)
            lg << "Parsing Setting : Ended " << Logger::endl;
    }
};

ostream &operator<<(ostream &o,ParserType p)
{
    switch (p)
    {
    case ParserType::LL1:
        o << "LL1";
        break;
    case ParserType::SLR:
        o << "SLR";
        break;
    case ParserType::CLR:
        o << "CLR";
        break;
    }
    return o;
}

#endif // ! _PARSER_HPP_
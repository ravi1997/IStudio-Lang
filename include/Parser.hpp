#ifndef _PARSER_HPP_
#define _PARSER_HPP_ 1

#ifndef _OPTIONS_HPP_
#include <options.hpp>
#endif // !_OPTIONS_HPP_

#ifndef _LOGGER_HPP_
#include <logger.hpp>
#endif // !_LOGGER_HPP_

#ifndef _GRAMMAR_HPP_
#include <grammar.hpp>
#endif // !_Grammar_HPP_

#ifndef _HANDLE_RULE_HPP_
#include <handlerule.hpp>
#endif

template <typename t>
class Parser
{
public:
private:
    mutable string code = "";
    mutable unsigned int line = 0;
    const string fileName;
    const Options options;
    vector<Terminal<t>> skipTerminals;
    Grammar<t> grammar;

    ParserTable<t> table;

public:
    Parser(string f, Grammar<t> gg, vector<string> o, vector<Terminal<t>> ng) : fileName{f}, options{o}, grammar{gg}
    {
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

    }

    void init(){
        Grammar<t> augmented=grammar.getAugmented();
        NonTerminal<t> s=augmented.getStart();
        vector<State<t>> states;
        Action<t> actionTable;
        Goto<t> gotoTable;
        size_t previousState=0;
        bool act=true;
        bool o=false;
        variant<NonTerminal<t>,Terminal<t>> element;
        vector<pair<State<t>, NonTerminal<t>>> GotoList;
        vector<pair<State<t>, Terminal<t>>> ActionList;
        State<t> I=s.getRules()[0].getHandleRule().getState(augmented,LookAheads<t>{Terminal<t>::DOLLAR});
        states.push_back(I);
        for (auto x : getGoto(I))
            GotoList.push_back(pair{I, x});

        for (auto x : getAction(I))
            ActionList.push_back(pair{I, x});
        do{
            if(find(states.begin(),states.end(),I)==states.end()){
                states.push_back(I);
                for(auto x:getGoto(I))
                    GotoList.push_back(pair{I,x});

                for (auto x : getAction(I))
                    ActionList.push_back(pair{I, x});
            }

            if(o && act)
                actionTable[states[previousState]][get<Terminal<t>>(element)] = pair{getSR(I), distance(find(states.begin(), states.end(), I), states.begin())};
            else
                gotoTable[states[previousState]][get<NonTerminal<t>>(element)] = distance(find(states.begin(), states.end(), I), states.begin());

            previousState = distance(find(states.begin(), states.end(), I), states.begin());
            if(GotoList.size()>0){
                State<t> temp=getNextState(augmented,GotoList.back().first,GotoList.back().second);
                element = GotoList.back().second;
                GotoList.pop_back();
                act=false;
                I.clear();
                I.insert(I.begin(),temp.begin(),temp.end());
            }
            else if(ActionList.size()>0){
                State<t> temp = getNextState(augmented,ActionList.back().first, ActionList.back().second);
                element = ActionList.back().second;
                ActionList.pop_back();
                I.clear();
                I.insert(I.begin(), temp.begin(), temp.end());
                act=true;
            }
            else{
                break;
            }
            o=true;
        }while(1);
    }


    const static Terminal<t> UNARYPRE;
    const static Terminal<t> UNARYPOST;
    const static Terminal<t> BINARY;
};

#endif // ! _PARSER_HPP_
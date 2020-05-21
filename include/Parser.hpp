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

    void init(NonTerminal<t> s){
        Logger lg;
        auto x = options.getLogger();
        if (x)
            lg = options.getLoggerFile();

        if (x)
            lg << "Parsing table : started"<< Logger::endl;

        Grammar<t> augmented=grammar.getAugmented(s);
        //NonTerminal<t> s=augmented.getStart();
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
        
       do{
            if(!find(states,I)){
               // cout<<"new State : "<<I<<endl;
                states.push_back(I);
                for(auto gt:getGoto(I))
                    GotoList.push_back(pair{I,gt});

                for (auto at : getAction(I))
                    ActionList.push_back(pair{I, at});
            }

            if(o && act){
                cout<<"action : state "<<previousState<<get<Terminal<t>>(element)<<" : "<<getSR(I)<<distance(states.begin(), find(states.begin(), states.end(), I))<<endl;
                actionTable[states[previousState]][get<Terminal<t>>(element)] = pair{getSR(I), distance(states.begin(), find(states.begin(), states.end(), I))};
            }
            else if(o && !act){
                cout<<"goto : state "<<previousState<<get<NonTerminal<t>>(element)<<" : "<<distance(states.begin(), find(states.begin(), states.end(), I))<<endl;
                gotoTable[states[previousState]][get<NonTerminal<t>>(element)] = distance(states.begin(), find(states.begin(), states.end(), I));
            }
        

            if(GotoList.size()>0){
                State<t> temp=getNextState(augmented,GotoList.back().first,GotoList.back().second);
                previousState = distance(states.begin(), find(states.begin(), states.end(), GotoList.back().first));
                element = GotoList.back().second;
                GotoList.pop_back();
                act=false;
                I.clear();
                for (auto t1 : temp)
                    I.push_back(t1);
            }
            else if(ActionList.size()>0){
                State<t> temp = getNextState(augmented,ActionList.back().first, ActionList.back().second);
                previousState = distance(states.begin(), find(states.begin(), states.end(), ActionList.back().first));
                element = ActionList.back().second;
                ActionList.pop_back();
                I.clear();
                for(auto t1:temp)
                    I.push_back(t1);
                act=true;
            }
            else{
                break;
            }
            o=true;
        }while(1);

        if (x)
            lg << "States Found are : " << Logger::endl;
        int i=0;

        for(auto s1:states){
            if (x)
                lg << "State "<<i << Logger::endl<<s1<<Logger::endl;
            i++;
        }

        if (x)
            lg << "Action Table " << Logger::endl;
/*
        cout<<actionTable.size()<<endl;

        //cout<<actionTable[states[0]].size()<<endl;

        for (auto s1 : states){
            cout<<"state "<<endl<<s1;
            for(auto [key,val]:actionTable[s1]){
                cout<<key<<" "<<val.first<<val.second<<endl;
            }
            
        }
*/    }

    const static Terminal<t> UNARYPRE;
    const static Terminal<t> UNARYPOST;
    const static Terminal<t> BINARY;
};

#endif // ! _PARSER_HPP_
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

        if(grammar.hasNull()){
            //cout<<grammar<<endl;
            grammar=grammar.removeNull();
        }


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
        vector<Terminal<t>> terminalList=augmented.getTerminals();
        vector<NonTerminal<t>> nonterminalList=augmented.getNonTerminals();
        terminalList.push_back(Terminal<t>::DOLLAR);
       do{
            if(!find(states,I)){
               // cout<<"new State : "<<I<<endl;
                states.push_back(I);
                for(auto gt:getGoto(I))
                    GotoList.push_back(pair{I,gt});

                for (auto at : getAction(I))
                    ActionList.push_back(pair{I, at});
                
                for (auto ts:terminalList)
                    actionTable[distance(states.begin(), find(states.begin(), states.end(), I))][distance(terminalList.begin(), find(terminalList.begin(), terminalList.end(), ts))] = pair{SR::EMPTY, 0};
                for (auto ts : augmented.getNonTerminals())
                    gotoTable[distance(states.begin(), find(states.begin(), states.end(), I))][distance(nonterminalList.begin(), find(nonterminalList.begin(), nonterminalList.end(), ts))] = INT_MAX;
            }

            if(o && act){
                //cout<<"action : state "<<previousState<<get<Terminal<t>>(element)<<" : "<<getSR(I)<<distance(states.begin(), find(states.begin(), states.end(), I))<<endl;
                actionTable[previousState][distance(terminalList.begin(), find(terminalList.begin(), terminalList.end(), get<Terminal<t>>(element)))] = pair{SR::SHIFT, distance(states.begin(), find(states.begin(), states.end(), I))};
                //cout << endl << getSR(states[previousState]) << endl;
            }
            else if(o && !act){
                //cout<<"goto : state "<<previousState<<get<NonTerminal<t>>(element)<<" : "<<distance(states.begin(), find(states.begin(), states.end(), I))<<endl;
                gotoTable[previousState][distance(nonterminalList.begin(), find(nonterminalList.begin(), nonterminalList.end(), get<NonTerminal<t>>(element)))] = distance(states.begin(), find(states.begin(), states.end(), I));
            }

            if (getSR(states[distance(states.begin(), find(states.begin(), states.end(), I))]) == SR::REDUCE)
                for (auto [rue, l] : states[distance(states.begin(), find(states.begin(), states.end(), I))])
                    for(auto lsss:l)
                        actionTable[distance(states.begin(), find(states.begin(), states.end(), I))][distance(terminalList.begin(), find(terminalList.begin(), terminalList.end(), lsss))] = pair{SR::REDUCE, distance(augmented.getRules().begin(), find(augmented.getRules().begin(), augmented.getRules().end(), rue.getRule()))};
                    

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
        size_t i=0;

        for(auto s1:states){
            if (x)
                lg << "State "<<i << Logger::endl<<s1<<Logger::endl;
            i++;
        }

        if (x){

          //  cout<<endl<<terminalList.size()<<endl;
    //        cout<<actionTable.size()<<endl;
    
            //cout<<actionTable[0].size()<<endl;
            lg<<"\t";
            for (auto term : terminalList)
                lg << "\t" << term;
            for (auto term : nonterminalList)
                lg << "\t" << term;
            lg<<Logger::endl;
            for (i=0;i<states.size();i++){
                lg<<"state "<<i<<"\t";
                for(size_t j=0;j<terminalList.size();j++){
                    //cout<<"\t"<<ts<<"\t";
                    auto ats=actionTable[i][j];
                    if(ats.first!=SR::EMPTY){
                        if(ats.first!=SR::REDUCE)
                            lg<<ats.first<<ats.second<<"\t|";
                        else if(ats.second!=terminalList.size()-1)
                            lg << ats.first << ats.second+1<< "\t|";
                        else
                            lg<<"accept\t|";
                    }
                    else
                        lg<<"\t|";
                }

                for (size_t j = 0; j < nonterminalList.size(); j++)
                {
                    //cout<<"\t"<<ts<<"\t";
                    auto ats = gotoTable[i][j];
                    if (ats != INT_MAX)
                        lg<<ats<<"\t|";
                    else 
                        lg << "\t|";
                }
                lg<<Logger::endl;
            }
        }
        grammar=augmented;
        table=pair{actionTable,gotoTable};
    }


    void startParsing() const {
        vector<NonTerminal<t>> nonterminalList = grammar.getNonTerminals();
        vector<Terminal<t>> terminalList = grammar.getTerminals();
        terminalList.push_back(Terminal<t>::DOLLAR);
        Action<t> actionTable = table.first;
        Goto<t> gotoTable = table.second;
        Logger lg;
        auto x = options.getLogger();
        if (x)
            lg = options.getLoggerFile();

        if (x)
            lg<<"Starting Parsing"<<Logger::endl;
        
        vector<int> stack;
        stack.push_back(0);

        Terminal<t> max=Terminal<t>::DOLLAR;

    
        vector<Token<t>> tokens;
        

        while (stack.size() != 0){
            max=Terminal<t>::DOLLAR;
            for(size_t i=0; i<terminalList.size(); i++)
                if(max.getMatch(code).length()<terminalList[i].getMatch(code).length())
                    max=terminalList[i];
            
            for(size_t i=0; i<skipTerminals.size();i++)
                if(max.getMatch(code).length()<skipTerminals[i].getMatch(code).length()){
                    code = code.substr(skipTerminals[i].getMatch(code).length(), code.length() - skipTerminals[i].getMatch(code).length());
                    //cout<<"ok"<<endl;
                    try{skipTerminals[i](*this); }catch(...){}
                    goto continuePoint;
                }
  
            cout<<code<<"\t"<<stack.back()<<"\t"<<max<<endl;

            if (max == Terminal<t>::DOLLAR && actionTable[stack.back()][terminalList.size() - 1].first == SR::REDUCE && actionTable[stack.back()][terminalList.size() - 1].second == grammar.getRules().size() - 1)
            {
                throw Successfull{};
            }

            if(actionTable[stack.back()][distance(terminalList.begin(),find(terminalList.begin(),terminalList.end(),max))].first!=SR::EMPTY){
                if (actionTable[stack.back()][distance(terminalList.begin(), find(terminalList.begin(), terminalList.end(), max))].first == SR::SHIFT)
                {
                    Token<t> token = Token{max.isOperator() ? max.getOperator(max.getMatch(code)) : max, max.getMatch(code)};
                    try{
                        token.first(*this);
                    }catch(...){}
                    tokens.push_back(token);
                    stack.push_back(actionTable[stack.back()][distance(terminalList.begin(), find(terminalList.begin(), terminalList.end(), max))].second);
                    code = code.substr(max.getMatch(code).length(), code.length() - max.getMatch(code).length());
                    //cout<<endl<<"ok2"<<endl;
                }
                else{
                    NonTerminal<t> ns = grammar.getRules()[actionTable[stack.back()][distance(terminalList.begin(), find(terminalList.begin(), terminalList.end(), max))].second].getLeft();
                    try{grammar.getRules()[actionTable[stack.back()][distance(terminalList.begin(), find(terminalList.begin(), terminalList.end(), max))].second](*this);}catch(...){}
                    
                    //cout<<endl << stack.back()<<endl;
                    for (size_t i = grammar.getRules()[actionTable[stack.back()][distance(terminalList.begin(), find(terminalList.begin(), terminalList.end(), max))].second].getRightAssociates().size(); i > 0; i--){
                        assert(stack.size()!=0);
                        //cout<<endl<<i<<endl;
                        stack.pop_back();
                    }
                    stack.push_back(gotoTable[stack.back()][distance(nonterminalList.begin(), find(nonterminalList.begin(), nonterminalList.end(), ns))]);
                }
            }
            else
                throw SyntaxError{};

            continuePoint:
                continue;
        }
    }

    const static Terminal<t> UNARYPRE;
    const static Terminal<t> UNARYPOST;
    const static Terminal<t> BINARY;
};

#endif // ! _PARSER_HPP_
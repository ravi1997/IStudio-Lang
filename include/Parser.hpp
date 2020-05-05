#ifndef _PARSER_HPP_
#define _PARSER_HPP_ 1


#ifndef _TYPES_HPP_
#include<types.hpp>
#endif // !_TYPES_HPP_

#ifndef _OPTIONS_HPP_
#include<options.hpp>
#endif // !_OPTIONS_HPP_

#ifndef _GRAMMAR_HPP_
#include<grammar.hpp>
#endif // !_OPTIONS_HPP_

#ifndef _HANDLE_RULE_HPP_
#include<handleRule.hpp>
#endif // !_HANDLE_RULE_HPP_

template<typename t>
class Parser{
    private:
        mutable string code="";
        mutable unsigned int line=0;
        const string fileName;
        const Options options;
        vector<Terminal<t>> skipTerminals;
        Grammar<t> grammar;

        using LL1Parser = map<NonTerminal<t>,map<Terminal<t>,Rule<t>>>;
        


        using LookAheads = vector<Terminal<t>>;
        using State = vector<pair<HandleRule,LookAheads>>;
        enum class SR{
            SHIFT,
            REDUCE
        };

        using Action = map<State,map<Terminal<t>,pair<SR,int>>>;
        using Goto = map<State,map<NonTerminal<t>,int>>;
        using SLRParser = pair<Action,Goto>;

        enum class ParserType{
            LL1,
            SLR
        };
        ParserType parserType;
        variant<LL1Parser,SLRParser> table;


    public:
        Parser(string f,Grammar<t> gg,vector<string> o,vector<Terminal<t>> ng,string s="LL0"):fileName{f},options{o},grammar{gg}{
            Logger lg;
            auto x=options.getLogger();
            if(x)
                lg=options.getLoggerFile();
           
            if(x)
                lg<<"Parsing started for : "<<fileName<<Logger::endl;

            ifstream file(fileName);
            if(!file.good())
                throw FileNotFound{};
           
            if(x)
                lg<<"File Opened Successfully : "<<fileName<<Logger::endl;
           
            if(x)
                lg<<"File character read : started"<<Logger::endl;
            char c;
            while(file>>noskipws>>c)
                code+=c;

            if(x)
                lg<<"File character read : successfull"<<Logger::endl;


            if(x)
                lg<<"Skip Character read : started"<<Logger::endl;

            for(auto st:ng)
                skipTerminals.push_back(st);

            if(x)
                lg<<"Skip Character read : successfull"<<Logger::endl;


            if(x)
                lg<<"Parser Type : "<<s<<Logger::endl;

            if(s=="LL0")
                parserType=ParserType::LL1;
            else
                parserType=ParserType::SLR;
        }


        Parser(const Parser& p):
            code{p.code},
            line{p.line},
            fileName{p.fileName},
            options{p.options},
            skipTerminals{p.skipTerminals},
            grammar{p.grammar},
            parserType{p.parserType},
            table{p.table}
            {}


        Parser(Parser&& p):
            code{move(p.code)},
            line{move(p.line)},
            fileName{move(p.fileName)},
            options{move(p.options)},
            skipTerminals{move(p.skipTerminals)},
            grammar{move(p.grammar)},
            parserType{move(p.parserType)},
            table{move(p.table)}
            {}

        Parser& operator=(const Parser& p){
            code=p.code;
            line=p.line;
            fileName=p.fileName;
            //options=p.options;
            skipTerminals=p.skipTerminals;
            grammar=p.grammar;
            parserType=p.parserType;
            table=p.table;
            return *this;
        }
        
        Parser& operator=(Parser&& p){
            code=move(p.code);
            line=move(p.line);
            fileName=move(p.fileName);
            //options=move(p.options);
            skipTerminals=move(p.skipTerminals);
            grammar=move(p.grammar);
            parserType=move(p.parserType);
            table=move(p.table);
            return *this;
        }
        ~Parser(){}


        void init(){
            Logger lg;
            auto xop=options.getLogger();
            if(xop)
                lg=options.getLoggerFile();
           
            switch(parserType){
                case ParserType::LL1 :  {
                                            if(xop)
                                                lg<<"LL1 Table setting : started"<<Logger::endl;
                                            LL1Parser lTable;
                                            
                                            for(auto x:grammar.getNonTerminals()){
                                                //lTable[x]=map<Terminal<t>,Rule<t>>{};
                                                for(auto y:x.getRules()){
                                                    for(auto z:y.getFirst()){
                                                        if(xop)
                                                            lg<<"LL1Table["<<x<<"]["<<z<<"] = "<<y<<Logger::endl;
                                            
                                                        lTable[x][z]=y;
                                                    }
                                                }
                                            }
                                            table=lTable;
                                        }
                                        break;
                default : break;
            }
        }


        void startParsing() const{
            Logger lg;
            auto xop=options.getLogger();
            if(xop)
                lg=options.getLoggerFile();
           
            vector<RightAssociate<t>> stack;
            if(xop)
                lg<<"Parsing status : started"<<Logger::endl;
            
            stack.push_back(RightAssociate<t>{RightAssociateType::NONTERMINAL,grammar.getStart()});
            if (xop)
                lg << "start symbol inserted : successfull" << Logger::endl;
            while(code!="" && stack.size()!=0){
                if(xop)
                {
                    lg<<"Stack size : "<<stack.size()<<Logger::endl;
                    lg<<"Stack entries are : "<<Logger::endl;
                    for(RightAssociate<t> i: stack)
                        lg <<"\t"<<i<<Logger::endl;
                }

                //cout<<stack.size()<<code<<endl;
                Terminal<t> max{Terminal<t>::EPSILON};
                for(auto x:grammar.getTerminals()){
                    if(max.getMatch(code).length()<x.getMatch(code).length())
                        max=x;
                }
                try{
                    //cout<<max<<endl;
                    //cout<<stack.back().first<<endl;
                    switch(stack.back().first){
                        case RightAssociateType::NONTERMINAL: {
                            RightAssociate<t> top=stack.back();
                            stack.pop_back();
                            //cout<<top<<endl;
                            if(get<NonTerminal<t>>(top.second)==NonTerminal<t>::Dollar){
                                if((*get<NonTerminal<t>>(top.second)->getThis()).hasAction()){
                                    (*get<NonTerminal<t>>(top.second)->getThis())(*this);
                                    (*get<NonTerminal<t>>(top.second)->getThis()).removeAction();
                                }
                                continue;
                            }
                            if(auto value1=get<LL1Parser>(table).find(get<NonTerminal<t>>(top.second));value1!=get<LL1Parser>(table).end()){
                                if(auto value2=value1->second.find(max);value2!=value1->second.end()){
                                    auto r=value2->second.getRightAssociates();
                                    
                                    NonTerminal dl{NonTerminal<t>::Dollar};
                                    //cout << (value2->second).hasAction()<<endl;
                                    if ((value2->second).hasAction())
                                        (*dl->getThis())((value2->second).getAction());

                                    //(value2->second)(*this);

                                    if ((*dl->getThis()).hasAction())
                                        cout<<"ok"<<endl;

                                    stack.push_back(RightAssociate<t>{RightAssociateType::NONTERMINAL, dl});

                                    for(auto it=r.rbegin(); it!=r.rend();it++){
                                        stack.push_back(*it);
                                    }
                                }
                                else
                                    throw SyntaxError{};
                            }
                            else
                                throw SyntaxError{};    
                        } 
                        break;
                        case RightAssociateType::TERMINAL: {
                            RightAssociate<t> top=stack.back();
                            stack.pop_back();
                            //cout<<get<Terminal<t>>(top.second)<<" == "<<max<<endl;
                            if(get<Terminal<t>>(top.second)==max){
                                code=code.substr(max.getMatch(code).length(),code.length());
                                max(*this);
                            }
                            else{
                                stack.push_back(top);
                                throw SyntaxError{};
                            }
                        }
                        break;
                    }

                }
                catch(SyntaxError){
                    //cout<<"catch(max) : "<<max<<endl;
                    if(max==Terminal<t>::EPSILON){
                        for(auto ts:skipTerminals){
                            if(ts.getMatch(code).length()>max.getMatch(code).length())
                                max=ts;
                        }
                        if(max==Terminal<t>::EPSILON)
                            throw SyntaxError{};
                        else{
                            max(*this);
                            code=code.substr(max.getMatch(code).length(),code.length());
                        }
                    }
                    else
                        throw SyntaxError{
                            string{"expected  : "} + max.getPattern(),
                            line,
                            fileName};
                }
                catch(...){
                    throw;
                }
            }
            if((code!="" && code!="\n") || stack.size()!=0)
                throw SyntaxError{
                    (code != "" && code != "\n") ?string{"Code is not finished\nCode is : "}+code
                    :string{"stack not empty\nStack size was : "}+to_string(stack.size()),
                    line,
                    fileName
                };

            if(xop)
                lg<<"Parsing status : Successfull"<<Logger::endl;

        }
};

#endif // !_PARSER_HPP_
#include<terminal.hpp>
#include<nonterminal.hpp>
#include<Parser.hpp>
#include<grammar.hpp>

#include<terminal.cpp>
#include<nonterminal.cpp>

int main([[maybe_unused]]int argc,[[maybe_unused]] char** argv){
    //cout<<"hello world"<<endl;

    if(argc<2){
        cerr<<"IStudioLang : Very few options"<<endl;
        cerr<<"Command : IStudioLang [options] filename"<<endl;
        return -1;
    }

    if(!regex_match(string{argv[0]},regex{"(\\.{0,1})(.*)(/bin/IStudioLang)"})){
        cerr<<"Unknown command running"<<endl;
        cerr<<"Command found is "<<argv[0]<<endl;
        return -1;
    }

    vector<string> options;
    for(auto i=1;i<argc-1;i++)
        options.push_back(argv[i]);
    try{
        Terminal<int> function{"(function)"};
        Terminal<int> id{"([A-Za-z][A-Za-z0-9]*)"};
        Terminal<int> squareOpenBracket{"(\\[)"};
        Terminal<int> parenthesisOpen{"(\\()"};
        Terminal<int> parenthesisClose{"(\\))"};
        Terminal<int> squareCloseBracket{"(\\])"};
        Terminal<int> character8{"char_8"};
        Terminal<int> character16{"char_16"};
        Terminal<int> character32{"char_32"};
        Terminal<int> character64{"char_64"};
        Terminal<int> int8{"int_8"};
        Terminal<int> int16{"int_16"};
        Terminal<int> int32{"int_32"};
        Terminal<int> int64{"int_64"};
        Terminal<int> comma{","};
        Terminal<int> space{"(\\s)"};


        NonTerminal<int> expression{"expression"};

        NonTerminal<int> functionDeclaration{"functionDeclaration"};
        NonTerminal<int> returnTypeList{"returnTypeList"};
        NonTerminal<int> ParameterList{"ParameterList"};
        NonTerminal<int> ParameterDash{"ParameterDash"};
        NonTerminal<int> Type{"Type"};
        NonTerminal<int> rdash{"rdash"};

        functionDeclaration->add(function, id, parenthesisOpen, parenthesisClose)([](const Parser<int> &) -> int {
            cout << "correct" << endl;
            return 0;
        }) 
        | add(function, squareOpenBracket, returnTypeList, squareCloseBracket, id, parenthesisOpen, parenthesisClose)
        | add(function, id, parenthesisOpen,ParameterList, parenthesisClose)
        | add(function, squareOpenBracket, returnTypeList, squareCloseBracket, id, parenthesisOpen, ParameterList, parenthesisClose)
        ;
        returnTypeList->add(Type,id,rdash);
        rdash->add(comma,Type,id,rdash)
        | add(comma,Type,id)
        ;

        ParameterList->add(Type, id, ParameterDash)
        | add(Type,id);
        ParameterDash->add(comma, Type, id, ParameterList) 
        | add(comma, Type,id);

        Type->add(character8) ([](const Parser<int>&)->int{
                    return 0;
              })
              |add(character16)
              |add(character32) ([](const Parser<int>&)->int{
                    return 0;
              })
              |add(character64)
              ;

        Grammar<int> g{
                        {
                            function,
                            id,
                            squareOpenBracket,
                            parenthesisOpen,
                            parenthesisClose,
                            squareCloseBracket,
                            character8,
                            character16,
                            character32,
                            character64,
                            int8,
                            int16,
                            int32,
                            int64,
                            comma,
                        },
                        {
                            expression,
                            functionDeclaration,
                            returnTypeList,
                            ParameterList,
                            Type,
                            rdash
                        },
                        functionDeclaration
        };


        Parser<int> p{
            argv[argc-1],
            g,
            options,
            {
                space
            }
        };

        p.init();
        try{
            p.startParsing();
        }
        catch(SyntaxError s){
            cout<<"Syntax Error : "<<s<<endl;
        }

       // cout<<"parsing completed"<<endl;

}catch(FileNotFound){
        cerr<<"IStudioLang : File not Found"<<endl;
        return -1;
    }
    catch(InvalidOption i){
        cerr<<"IStudioLang:invalid option "<<i<<endl;
        cerr<<"IStudioLang:Use help to see all options"<<endl;
        cerr<<"Command: IStudioLang -help"<<endl;
        return -1;
    }
    catch(HelpOption){
        cout<<"IStudioLang (1.0.1)"<<endl;
        cout<<"It is a compiler that works for IStudio language"<<endl<<endl;
        cout <<"Command : IStudioLang [options] filename" << endl<<endl;
        cout <<"Options" << endl;
        cout<<"\t[-g][-gdb]\t\tDebug options"<<endl;
        cout<<"\t[-h][-help]\t\tShow this help"<<endl;
        cout<<"\t[-I][-include]\t\tInclude options"<<endl;
        cout<<"\t[-o][-output]\t\tOutput file options"<<endl;
        cout<<"\t[-l][-logger]\t\tLogger file options"<<endl<<endl;
        return 0;
    }

    catch(FewOptions){
        cerr<<"IStudioLang : Very few options"<<endl;
        cerr<<"Command : IStudioLang [options] filename"<<endl;
        return -1;
    }
    return 0;
}

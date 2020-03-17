#include<iostream>
#include<parser.hpp>
#include<DAG.hpp>

#include<terminal.cpp>
using namespace std;


int main(int argc,char**argv){
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
      //  cout<<sizeof(NonTerminal<DAG>)<<endl;
      //cout<<sizeof(Terminal<DAG>)<<endl;

        Terminal<DAG> function{"(function)"};
        Terminal<DAG> id{"([A-Za-z][A-Za-z0-9]*)"};
        Terminal<DAG> squareOpenBracket{"(\\[)"};
        Terminal<DAG> parenthesisOpen{"(\\()"};
        Terminal<DAG> parenthesisClose{"(\\))"};
        Terminal<DAG> squareCloseBracket{"(])"},comma{","};
        Terminal<DAG> character8{"char_8"};
        Terminal<DAG> character16{"char_16"};
        Terminal<DAG> character32{"char_32"};
        Terminal<DAG> character64{"char_64"};
        Terminal<DAG> int8{"int_8"};
        Terminal<DAG> int16{"int_16"};
        Terminal<DAG> int32{"int_32"};
        Terminal<DAG> int64{"int_64"};

        NonTerminal<DAG> functionDeclaration,returnTypeList,ParameterList,expression;
        NonTerminal<DAG> Type,rdash;

        functionDeclaration->add(function,squareOpenBracket,returnTypeList,squareCloseBracket,id,parenthesisOpen,ParameterList,parenthesisClose);
        returnTypeList->add(Type,id,comma,rdash);
        expression->add();
        Type->add(character8)
              |add(character16)

              ;

        Grammar<DAG> g{{function,squareOpenBracket,squareCloseBracket,id},{functionDeclaration},functionDeclaration};
        Parser<DAG> p{argv[argc-1],options};
        p.setGrammar(g);

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

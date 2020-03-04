#include<iostream>
#include<parser.hpp>
#include<DAG.hpp>

#include<terminal.cpp>
#include<rule.cpp>
#include<rules.cpp>
using namespace std;


int main(int argc,char**argv){
    if(argc<2){
        cerr<<"IStudioLang : Very few options"<<endl;
        cerr<<"Command : IStudioLang [options] filename"<<endl;
        return -1;
    }

    if(string{argv[0]}!=string{"./bin/IStudioLang"}){
        cerr<<"Unknown command running"<<endl;
        return -1;
    }

    vector<string> options;
    for(auto i=1;i<argc-1;i++)
        options.push_back(argv[i]);
    try{

        Terminal function{"(function)"};
        Terminal id{"([A-Za-z][A-Za-z0-9]*)"};
        Terminal squareOpenBracket{"(\\[)"};
        Terminal parenthesisOpen{"(\\()"};
        Terminal parenthesisClose{"(\\))"};
        Terminal squareCloseBracket{"(])"};

        NonTerminal<DAG> functionDeclaration;

        functionDeclaration->add(function,squareOpenBracket,squareCloseBracket,id,parenthesisOpen,parenthesisClose);

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

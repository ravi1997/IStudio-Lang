#include<iostream>
#include<parser.hpp>
#include<grammar.hpp>


#include<nonterminal.cpp>
#include<rule.cpp>
#include<rules.cpp>
using namespace std;

class InvalidOption{
    string s;
public:
    InvalidOption(string x):s{x}{}
    friend ostream& operator<<(ostream& o,InvalidOption i){
        o<<i.s;
        return o;
    }
};

class HelpOption{};
class FewOptions{};

class Options{
private:
    bool debug=false;
    bool graph=false;
    bool output=false;
    string outputFile="";
    bool includePath=false;
    string includePaths="";
public:
    Options(vector<string> s){
        for(auto x=s.begin(),z=s.end();x!=z;x++)
            if((*x=="-g")|| (*x=="-debug"))
                debug=true;
            else if((*x=="-G")||(*x=="-graph"))
                graph=true;
            else if ((*x=="-o")|| (*x=="-output")){
                output=true;
                x++;
                if(x==s.end())
                    throw FewOptions{};
                outputFile=*x;
            }
            else if ((*x=="-I")|| (*x=="-Include")){
                includePath=true;
                x++;
                if(x==s.end())
                    throw FewOptions{};
                includePaths=*x;
            }
            else if((*x=="-h")||(*x=="-help"))
                throw HelpOption{};
            else
                throw InvalidOption{*x};
    }
    bool getGraphFlag()const{
        return graph;
    }
    bool getOutputFlag()const{
        return output;
    }
    bool getIncludePathFlag()const{
        return debug;
    }
    string getOutputFile()const{
        return outputFile;
    }
    string getIncludePath()const{
        return includePaths;
    }

};


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
        Terminal id{"([A-Za-z_][A-Za-z0-9_]*)"};
        Terminal squareOpenBracket{"(\[)"};
        Terminal squareCloseBracket{"(])"};

        NonTerminal<int> functionDeclaration;

        functionDeclaration->add(function,squareOpenBracket,squareCloseBracket,id);

        Grammar<int> g{{function,squareOpenBracket,squareCloseBracket,id},{functionDeclaration}};
        Parser<Options,int> p{argv[argc-1],options};
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
        cout<<"\t[-o][-output]\t\tOutput file options"<<endl<<endl;
        return 0;
    }
    catch(FewOptions){
        cerr<<"IStudioLang : Very few options"<<endl;
        cerr<<"Command : IStudioLang [options] filename"<<endl;
        return -1;
    }
    return 0;
}

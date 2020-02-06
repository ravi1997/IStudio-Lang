#include<iostream>
#include<parser.hpp>
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
        Parser p{argv[argc-1],options};
    }catch(FileNotFound){
        cerr<<"IStudioLang : File not Found"<<endl;
        return -1;
    }

    return 0;
}
#include<iostream>
#include<parser.hpp>
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
                outputFile=*x;
            }
            else if ((*x=="-I")|| (*x=="-Include")){
                includePath=true;
                x++;
                includePaths=*x;
            }
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
        Parser<Options> p{argv[argc-1],options};
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

    return 0;
}
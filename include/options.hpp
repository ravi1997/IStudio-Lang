#ifndef _OPTIONS_HPP_
#define _OPTIONS_HPP_


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


#endif
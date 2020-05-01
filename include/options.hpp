#ifndef _OPTIONS_HPP_
#define _OPTIONS_HPP_ 1



#ifndef _TYPES_HPP_
#include<types.hpp>
#endif // !_TYPES_HPP_


#ifndef _LOGGER_HPP_
#include<logger.hpp>
#endif // !_LOGGER_HPP_

class Options{
private:
    bool debug=false;
    bool graph=false;
    bool output=false;
    string outputFile="";
    bool includePath=false;
    string includePaths="";
    bool logger=false;
    Logger loggerFile;
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
            else if((*x=="-lf")||(*x=="-loggerFile")){
                logger=true;
                x++;
                if(x==s.end())
                    throw FewOptions{};
                loggerFile=Logger{*x};
            }
            else if((*x=="-l")||(*x=="-logger")){
                logger=true;
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
    bool getLogger() const{
        return logger;
    }
    string getOutputFile()const{
        return outputFile;
    }
    string getIncludePath()const{
        return includePaths;
    }
    Logger getLoggerFile()const{
        return loggerFile;
    }
};


#endif
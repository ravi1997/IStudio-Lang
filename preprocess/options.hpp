#ifndef _OPTIONS_HPP_
#define _OPTIONS_HPP_ 1

#ifndef _TYPES_HPP_
#include"types.hpp"
#endif // !_TYPES_HPP_


#ifndef _LOGGER_HPP_
#include"logger.hpp"
#endif // !_LOGGER_HPP_

class Options{
private:
    bool debug=false;
    bool output=false;
    string outputFile = "";
    bool input=false;
    string inputFile = "";
    bool logger=false;
    Logger loggerFile;
public:
    Options(vector<string> s){
        for(auto x=s.begin(),z=s.end();x!=z;x++)
            if((*x=="-g")|| (*x=="-debug"))
                debug=true;
            else if ((*x=="-o")|| (*x=="-output")){
                output=true;
                x++;
                if(x==s.end())
                    throw FewOptions{};
                outputFile=*x;
            }
            else if ((*x == "-I") || (*x == "-input"))
            {
                input = true;
                x++;
                if (x == s.end())
                    throw FewOptions{};
                inputFile = *x;
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
    bool getOutputFlag()const{
        return output;
    }
    string getOutputFile()const{
        return outputFile;
    }
    bool getLoggerFlag()const{
        return logger;
    }
    Logger& getLoggerFile(){
        return loggerFile;
    }
    bool getDebugFlag()const{
        return debug;
    }
    bool getInputFlag() const
    {
        return input;
    }
    string getInputFile() const
    {
        return inputFile;
    }
};


#endif
#include<iostream>
#include<fstream>
#include<json.hpp>

using namespace std;
using json = nlohmann::json;

int main(int, char** argv)
{
    ofstream intermediate{"intermediate"};
    if (!intermediate)
    {
        cerr << "Error In Opening Intermediate" << endl;
        return -1;
    }
    ofstream grammers{"grammers"};
    if (!grammers)
    {
        cerr << "Error In Opening grammers" << endl;
        return -1;
    }
    ifstream fread2;
    string str;

    /////////////////////////////////////////////////////////////////
    //              configuration file                             //
    /////////////////////////////////////////////////////////////////
    ifstream configuration{argv[2]};
    if(!configuration)   {
        cerr<<"Error In Opening Target File..!! cfg";
        return -1;
    }
    json j;
    configuration>>j;
    configuration.close();


    ////////////////////////////////////////////////////////////////
    //                  input files                               //
    ////////////////////////////////////////////////////////////////
    
    grammers<<R"(
        Grammar<PARSERTYPE> g{
            {)"<<endl;
    
    ifstream input{j["nonterminal"]};
    if(!input) {
        cerr<<"Error In Opening NonTerminal"<<endl;
        return -1;
    }
    while (getline(input, str)){
        intermediate << "N(" << str << ");" << endl;
        grammers << str<< ',' << endl;
    }
    input.close();

    grammers<<R"(
        },
        {)"<<endl;

    input.open(j["terminal"]);
    if (!input)
    {
        cerr << "Error In Opening NonTerminal" << endl;
        return -1;
    }
    while (getline(input, str))
    {
        intermediate << "T(" << str << ");" << endl;
        grammers << str << ',' << endl;
    }
    input.close();

    input.open(j["rules"]);
    if (!input)
    {
        cerr << "Error In Opening NonTerminal" << endl;
        return -1;
    }
    while (getline(input, str))
        intermediate << str << endl;
    input.close();


    grammers<<R"(
        },
        )"<<endl;

    grammers << j["startsymbol"]<<endl;
    grammers << R"(
        };
    )"<<endl;
    intermediate.close();

    ofstream output{argv[1]};
    if(!output)   {
        cerr<<"Error In Opening output"<<endl;
        return -1;
    }

    vector<string> files{
        "source/header.cpp",
        "intermediate",
        "grammers",
        "source/foot.cpp"
    };

    for(auto file:files){
        ifstream temp{file};
        if(!temp){
            cerr<<"Error opening : "<<file<<endl;
            return -1;
        }
        while(getline(temp, str))
            output<<str<<endl;

        temp.close();
    }

    return 0;
}


#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include"csv.hpp"
#include"json.hpp"
using namespace std;
using json = nlohmann::json;

int main(int argc, char **argv)
{
    ifstream file{"test/config.json"};
    json myjson;
    file>>myjson;

    string terminalOutput = "output/terminalList.hpp";
    ofstream terminal{terminalOutput};

    string nonterminalOutput = "output/nonterminalList.hpp";
    ofstream nonterminal{nonterminalOutput};

    vector<string> o;
    for (auto i = 1; i < argc - 1; i++)
        o.push_back(argv[i]);
    Options options{o};
    CSV csvTerminal{myjson["terminal"], options};
    CSV csvNonTerminal{myjson["nonterminal"], options};

    terminal << "#ifndef _TERMINAL_LIST_HPP_" << endl;
    terminal << "#define _TERMINAL_LIST_HPP_ 1" << endl;

    for(auto [key,value]:csvTerminal)
        terminal<<"T("<<key<<",\""<<value<<"\");"<<endl;

    terminal<<"#endif"<<endl;

    nonterminal << "#ifndef _NONTERMINAL_LIST_HPP_" << endl;
    nonterminal << "#define _NONTERMINAL_LIST_HPP_ 1" << endl;

    for (auto [key, value] : csvTerminal)
        terminal << "N(" << key << ",\"" << value << "\");" << endl;

    terminal << "#endif" << endl;

    return 0;
}
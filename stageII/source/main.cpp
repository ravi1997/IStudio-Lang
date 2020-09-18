#include <parser.hpp>
#include <flowControl.hpp>
#define PARSERTYPE FlowControlNode
#define TERMINAL Terminal<PARSERTYPE>
#define NONTERMINAL NonTerminal<PARSERTYPE>

#include <terminal.cpp>
int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{

    vector<string> options;
    for (auto i = 1; i < argc - 1; i++)
        options.push_back(argv[i]);
    try
    {
        TERMINAL function{"function"};
        TERMINAL squareOpen{"\\["};
        TERMINAL squareClose{"\\]"};
        TERMINAL ID{"[_a-zA-Z][_a-zA-Z0-9]*"};

        TERMINAL parenthesisOpen{"\\("};
        TERMINAL parenthesisClose{"\\)"};

        TERMINAL curlyOpen{"\\{"};
        TERMINAL curlyClose{"\\}"};

        TERMINAL comma{","};
        TERMINAL Return{"return"};
        TERMINAL readOnly{"readonly"};
        TERMINAL writeOnly{"writeonly"};
        TERMINAL moveOnly{"moveonly"};
        TERMINAL readWrite{"readwrite"};
        TERMINAL readMove{"readmove"};
        TERMINAL writeMove{"writemove"};

        TERMINAL Export{"export"};
        TERMINAL Constexpr{"constexpr"};
        TERMINAL Consteval{"consteval"};
        TERMINAL Nullptr{"nullptr"};
        TERMINAL throws{"throws"};
        TERMINAL Expect{"expect"};
        TERMINAL Ensures{"ensures"};

        TERMINAL Int_8{"int_8"};
        TERMINAL Int_16{"int_16"};
        TERMINAL Int_32{"int_32"};
        TERMINAL Int_64{"int_64"};

        TERMINAL Uint_8{"uint_8"};
        TERMINAL Uint_16{"uint_16"};
        TERMINAL Uint_32{"uint_32"};
        TERMINAL Uint_64{"uint_64"};

        TERMINAL char_8{"char_8"};
        TERMINAL char_16{"char_16"};
        TERMINAL char_32{"char_32"};

        TERMINAL Float{"float"};
        TERMINAL Double{"double"};
        TERMINAL Byte{"byte"};

        TERMINAL Equal{"="};

        NONTERMINAL functionDeclaration{"functionDeclaration"};
        NONTERMINAL returnParams{"returnParams"};
        NONTERMINAL params{"params"};

        Terminal<PARSERTYPE> space{"\\s"};

        function.setAction([](const Parser<PARSERTYPE> &) -> PARSERTYPE {
            //cout << "function";
            return PARSERTYPE{};
        });

        squareOpen.setAction([](const Parser<PARSERTYPE> &) -> PARSERTYPE {
            //cout << "squareOpen";
            return PARSERTYPE{};
        });

        squareClose.setAction([](const Parser<PARSERTYPE> &) -> PARSERTYPE {
            //cout << "squareClose";
            return PARSERTYPE{};
        });

        functionDeclaration->add(function, squareOpen, returnParams, squareClose, ID, parenthesisOpen, params, parenthesisClose, curlyOpen, curlyClose);
        returnParams->add();
        params->add();

        Grammar<PARSERTYPE> g{
            {function,
             squareOpen,
             squareClose,
             ID,
             Terminal<PARSERTYPE>::EPSILON,
             parenthesisOpen,
             parenthesisClose,
             curlyOpen,
             curlyClose},
            {functionDeclaration,
             returnParams,
             params},
            functionDeclaration};

        NONTERMINAL sdash{"sdash"};

        sdash->add(functionDeclaration);

        //cout<<A.getFirst().size()<<endl;

        Parser<PARSERTYPE> p{
            argv[argc - 1],
            g,
            options,
            {space}};

        p.init(sdash);
        
        /*try
        {
            p.startParsing();
        }
        catch (Successfull)
        {
            cout << "Parsing done" << endl;
        }*/
    }
    catch (FileNotFound)
    {
        cerr << "IStudioLang : File not Found" << endl;
        return -1;
    }
    catch (InvalidOption i)
    {
        cerr << "IStudioLang:invalid option " << i << endl;
        cerr << "IStudioLang:Use help to see all options" << endl;
        cerr << "Command: IStudioLang -help" << endl;
        return -1;
    }
    catch (HelpOption)
    {
        cout << "IStudioLang (1.0.1)" << endl;
        cout << "It is a compiler that works for IStudio language" << endl
             << endl;
        cout << "Command : IStudioLang [options] filename" << endl
             << endl;
        cout << "Options" << endl;
        cout << "\t[-g][-gdb]\t\tDebug options" << endl;
        cout << "\t[-h][-help]\t\tShow this help" << endl;
        cout << "\t[-I][-include]\t\tInclude options" << endl;
        cout << "\t[-o][-output]\t\tOutput file options" << endl;
        cout << "\t[-l][-logger]\t\tLogger file options" << endl
             << endl;
        return -1;
    }

    catch (FewOptions)
    {
        cerr << "IStudioLang : Very few options" << endl;
        cerr << "Command : IStudioLang [options] filename" << endl;
        return -1;
    }
    return 0;
}

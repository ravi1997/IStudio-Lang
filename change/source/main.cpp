#include <parser.hpp>
#include <terminal.cpp>

int main([[maybe_unused]]int argc,[[maybe_unused]] char** argv){

    if(argc<2){
        cerr<<"IStudioLang : Very few options"<<endl;
        cerr<<"Command : IStudioLang [options] filename"<<endl;
        return -1;
    }

    if(!regex_match(string{argv[0]},regex{"(\\.{0,1})(.*)(/bin/IStudioLang)"})){
        cerr<<"Unknown command running"<<endl;
        cerr<<"Command found is "<<argv[0]<<endl;
        return -1;
    }

    vector<string> options;
    for(auto i=1;i<argc-1;i++)
        options.push_back(argv[i]);
    try{
        //cout<<argv[argc-1]<<endl;
        if (regex_match(string{argv[argc - 1]}, regex{"(.*)(\\.)(iFunction)"}))
        {
            Terminal<int> function{"(function)"};
            Terminal<int> id{"([A-Za-z][A-Za-z0-9]*)"};
            Terminal<int> squareOpenBracket{"(\\[)"};
            Terminal<int> squareCloseBracket{"(\\])"};
            Terminal<int> parenthesisOpen{"(\\()"};
            Terminal<int> parenthesisClose{"(\\))"};
            Terminal<int> curlyBracketOpen{"(\\{)"};
            Terminal<int> curlyBracketClose{"(\\})"};
            Terminal<int> character8{"char_8"};
            Terminal<int> character16{"char_16"};
            Terminal<int> character32{"char_32"};
            Terminal<int> character64{"char_64"};
            Terminal<int> int8{"int_8"};
            Terminal<int> int16{"int_16"};
            Terminal<int> int32{"int_32"};
            Terminal<int> int64{"int_64"};
            Terminal<int> comma{","};
            Terminal<int> space{"(\\s)"};
            Terminal<int> exportKeyword{"(export)"};
            Terminal<int> constexprKeyword{"(constexpr)"};
            Terminal<int> constevalKeyword{"(consteval)"};
            Terminal<int> readonly{"(readonly)"};
            Terminal<int> moveonly{"(moveonly)"};
            Terminal<int> moveonly{"(moveonly)"};
            Terminal<int> readmove{"(readmove)"};

            NonTerminal<int> expression{"expression"};
            NonTerminal<int> functionDeclaration{"functionDeclaration"};
            NonTerminal<int> returnTypeList{"returnTypeList"};
            NonTerminal<int> ParameterList{"ParameterList"};
            NonTerminal<int> ParameterDash{"ParameterDash"};
            NonTerminal<int> Type{"Type"};
            NonTerminal<int> rdash{"rdash"};
            NonTerminal<int> exportCheck{"exportCheck"};
            NonTerminal<int> constexprCheck{"constexprCheck"};
            NonTerminal<int> returnType{"returnType"};
            NonTerminal<int> name{"name"};
            NonTerminal<int> parameterList{"parameterList"};
            NonTerminal<int> exceptionSyntax{"exceptionSyntax"};
            NonTerminal<int> Attributes{"Attributes"};
            NonTerminal<int> Contracts{"Contracts"};
            NonTerminal<int> statements{"statements"};
            NonTerminal<int> returnInitialisationType{"returnInitialisationType"};
            NonTerminal<int> returnTypeCheck{"returnTypeCheck"};
            NonTerminal<int> returnList{"returnList"};
            NonTerminal<int> initialization{"initialization"};
            NonTerminal<int> returnInitialisation{"returnInitialisation"};

            functionDeclaration->add(function, exportCheck, constexprCheck, returnType, name, parenthesisOpen, parameterList, parenthesisClose, exceptionSyntax, Attributes, Contracts, curlyBracketOpen, statements, curlyBracketClose);
            exportCheck->add(exportKeyword)
                        |add(Terminal<int>::EPSILON);

            constexprCheck->add(constexprKeyword)
                            |add(constevalKeyword)
                            |add(Terminal<int>::EPSILON);
            
            returnType->add(returnInitialisationType,Type)
                            |add(squareOpenBracket,returnList,squareCloseBracket)
                            |add(Terminal<int>::EPSILON);

            returnList->add(returnInitialisationType,Type,id,initialization,rdash);

            rdash->add(comma,returnInitialisationType,Type,id,initialization)
                    |add(Terminal<int>::EPSILON);

            name->add(id)
                //|add(operatoroverload)
                ;
            returnInitialisation->add(readonly)
                                |add(moveonly)
                                |add(readmove)
                                |add(squareOpenBracket,returnInitialisationList,squareCloseBracket);

            Grammar<int> g{
                {
                    function,
                    id,
                    squareOpenBracket,
                    parenthesisOpen,
                    parenthesisClose,
                    squareCloseBracket,
                    character8,
                    character16,
                    character32,
                    character64,
                    int8,
                    int16,
                    int32,
                    int64,
                    comma,
                },
                {expression,
                 functionDeclaration,
                 returnTypeList,
                 ParameterList,
                 Type,
                 rdash},
                functionDeclaration};

            Parser<int> p{
                argv[argc - 1],
                g,
                options,
                {space}};
        }
        }
        catch (FileNotFound)
        {
            cerr << "IStudioLang : File not Found" << endl;
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
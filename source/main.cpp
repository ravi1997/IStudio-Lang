#include<parser.hpp>

#include<terminal.cpp>
int main([[maybe_unused]]int argc,[[maybe_unused]] char** argv){
    //cout<<"hello world"<<endl;

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
    try
    {
        if (regex_match(string{argv[argc - 1]}, regex{"(.*)(\\.)(iFunction)"}))
        {
            Terminal<int> a{"a"};
            Terminal<int> b{"b"};

            NonTerminal<int> S{"S"};
            NonTerminal<int> A{"A"};

            S->add(A, A);
            A->add(a, A) | add(b);

            Grammar<int> g{
                {
                    a,
                    b
                },
                {
                    S,
                    A
                },
                S
            };


            NonTerminal<int> sdash{"sdash"};

            sdash -> add(S);

            //cout<<A.getFirst().size()<<endl;

            Parser<int> p{
                argv[argc - 1],
                g,
                options,
                {}};
  
            p.init(sdash);

        }
    }
    catch (FileNotFound)
    {
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
        cout<<"\t[-o][-output]\t\tOutput file options"<<endl;
        cout<<"\t[-l][-logger]\t\tLogger file options"<<endl<<endl;
        return -1;
    }

    catch(FewOptions){
        cerr<<"IStudioLang : Very few options"<<endl;
        cerr<<"Command : IStudioLang [options] filename"<<endl;
        return -1;
    }
    return 0;
}

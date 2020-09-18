  Grammar x = g.reduce();

        ofstream ntFile{"output/nonTerminal.txt", ios::out};

        for (auto nts : x.getNonTerminals())
            ntFile << nts << endl;

        ntFile.close();

        ofstream tFile{"output/terminal.txt", ios::out};

        for (auto nts : x.getTerminals())
            tFile << nts << endl;

        tFile.close();

        ofstream rFile{"output/rules.txt", ios::out};

        for (auto nts : x.getNonTerminals())
        {
            for (auto rts : nts.getRules())
                rFile << rts << endl;
        }
        rFile.close();
    }
    catch (FileNotFound f)
    {
        cerr << "IStudioLang : " << f << " not Found" << endl;
        return -1;
    }

    return 0;
}


OBJECTS=Object/terminal.o	\
				Object/nonterminal.o	\
				Object/Rules.o	\
				Object/rule.o


Object/%.o:source/%.cpp
	g++ -Iinclude -fconcepts -std=c++2a -Wall -Wextra -c $< -o $@

bin/IStudioLang:$(OBJECTS)
	g++ -Iinclude -std=c++2a -fconcepts -Wall -Wextra source/main.cpp $< -o $@

all : clean bin/IStudioLang
	./bin/IStudioLang test/t1.is

clean:
	rm -rf bin/* Object/*

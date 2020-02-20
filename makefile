OBJECTS=Object/terminal.o


Object/%.o:source/%.cpp
	g++ -Iinclude -fconcepts -std=c++2a -Wall -Wextra -c $< -o $@

bin/IStudioLang:$(OBJECTS)
	g++ -Iinclude -Isource -std=c++2a -fconcepts -Wall -Wextra source/main.cpp $< -o $@

all : clean bin/IStudioLang
	./bin/IStudioLang -g test/t1.is && true

clean:
	rm -rf bin/* Object/*

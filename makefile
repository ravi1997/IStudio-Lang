OBJECTS=Object/terminal.o


Object/%.o:source/%.cpp
	g++ -Iinclude -fconcepts -std=c++2a -Wall -Wextra -c -g -O0 $< -o $@

bin/IStudioLang:
	g++ -Iinclude -Isource -std=c++2a -fconcepts -Wall -Wextra -g source/main.cpp -O0$< -o $@

all : clean bin/IStudioLang
	./bin/IStudioLang -g test/t1.is && true

clean:
	rm -rf bin/* Object/*

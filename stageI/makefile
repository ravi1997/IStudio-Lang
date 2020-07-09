CC = g++
CCPARAMS = -ggdb -O3 -Wall -Wextra -Werror -Wshadow -std=c++2a -fconcepts -Iinclude -Isource -Itest -pedantic
PARAMS = -g -lf log/Logger.log
Target = bin/IStudioLang

Object/%.o:source/%.cpp
	$(CC) $(CCPARAMS) $< -o $@

bin/IStudioLang:clean
	$(CC) $(CCPARAMS) source/main.cpp -o $@

all:$(Target)
	./$(Target) -lf log/logger.log -I test/config.json iFunction

clean:
	(rm bin/* log/*.*)||true;

run:
	./$(Target) -lf log/logger.log -I test/config.json iFunction

setup:
	(mkdir bin) || true;
	(mkdir include) || true;
	(mkdir source) || true;
	(mkdir Object) || true;
	echo '' >> source/main.cpp

debug:clean $(Target)
	gdb ./$(Target)

.PHONY: all test clean setup debug

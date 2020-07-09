CC = g++
CCPARAMS = -ggdb -O3 -Wall -Wextra -Werror -Wshadow -std=c++2a -fconcepts -pedantic
PARAMS = -g -lf log/Logger.log
Target = bin/IStudioLang

Object/%.o:source/%.cpp
	$(CC) $(CCPARAMS) $< -o $@

bin/IStudioLang:clean
	$(CC) $(CCPARAMS) main.cpp -o $@

all:$(Target)
	./$(Target) -lf log/logger.log -I test/config.json iFunction

clean:
	(rm bin/* log/*.*)||true;

setup:
	(mkdir log) || true;
	(mkdir test) || true;
	(mkdir bin) || true;
	(mkdir output) || true;
	e cho '' >> source/main.cpp

debug:clean $(Target)
	gdb ./$(Target)

.PHONY: all test clean setup debug

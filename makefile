CC = g++
CCPARAMS = -g -O3 -Wall -Wextra -Werror -Wshadow -std=c++2a -fconcepts -Iinclude -Isource -pedantic
PARAMS = -g -lf log/Logger.log
Target = bin/IStudioLang
TEST = $(wildcard test/*.*)

Object/%.o:source/%.cpp
	$(CC) $(CCPARAMS) $< -o $@

bin/IStudioLang:clean
	$(CC) $(CCPARAMS) source/main.cpp -o $@

all:$(Target)
	$(MAKE) --no-print-directory test

clean:
	(rm bin/* log/*.*)||true;

test:
	(rm log/Logs.log)||true;
	for x in $(TEST); do ./$(Target) $(PARAMS) $$x; cat log/Logger.log >> log/Logs.log; done

setup:
	(mkdir bin) || true;
	(mkdir include) || true;
	(mkdir source) || true;
	(mkdir Object) || true;
	echo '' >> source/main.cpp

debug:clean $(Target)
	gdb ./$(Target)

.PHONY: all test clean setup debug

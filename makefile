CC = g++
CCPARAMS = -g -O3 -Wall -Wextra -std=c++2a -fconcepts -Iinclude -Isource
Target = bin/IStudioLang


Object/%.o:source/%.cpp
	$(CC) $(CCPARAMS) $< -o $@

bin/IStudioLang:clean
	$(CC) $(CCPARAMS) source/main.cpp -o $@

all:$(Target)
	$(MAKE) --no-print-directory test

clean:
	(rm $(Target))||true;

test:
	./$(Target) -lf log/Logger.log -g test/t1.is

setup:
	(mkdir bin) || true;
	(mkdir include) || true;
	(mkdir source) || true;
	(mkdir Object) || true;
	echo '' >> source/main.cpp

debug:clean $(Target)
	gdb ./$(Target)

.PHONY: all test clean setup debug

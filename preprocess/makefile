CC = g++
CCPARAMS = -ggdb -O3 -Wall -Wextra -Werror -Wshadow -std=c++2a -Iinclude -Isource -Itest -pedantic
PARAMS = -g -lf log/Logger.log
Target = bin/compiler

Object/%.o:source/%.cpp
	$(CC) $(CCPARAMS) $< -o $@

$(Target):clean
	$(CC) $(CCPARAMS) source/main.cpp -o $@

clean:
	(rm bin/* log/*.* output/*.* intermediate)||true;

run:
	./$(Target) output/main.cpp test/cfg.json

setup:
	(mkdir bin) || true;
	(mkdir include) || true;
	(mkdir source) || true;
	(mkdir Object) || true;
	echo '' >> source/main.cpp

debug:clean $(Target)
	gdb ./$(Target)

all:$(Target)
	$(MAKE) --no-print-directory run

.PHONY: all test clean setup debug

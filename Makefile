CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

SRC = $(wildcard src/*.c) $(wildcard src/*/*.c)
TESTS = tests/test_runner.c tests/test_parser.c tests/test_validator.c

.PHONY: all test clean

all:
	$(CC) src/*.c main.c -Iinclude -Wall -Wextra -mconsole -o analyzer


test:
	$(CC) $(TESTS) $(SRC) $(CFLAGS) -o test_runner
	./test_runner

run: all
	./analyzer

clean:
	rm -f analyzer test_runner

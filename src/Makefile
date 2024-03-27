SYSSHELL:=$(shell uname)
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -g
ifeq ($(SYSSHELL), Linux)
TFLAGS=-lcheck -lpthread -lrt -lsubunit --coverage -lm
else
TFLAGS=$(shell pkg-config --cflags --libs check) --coverage
endif

.PHONY: all s21_matrix.a test gcov_report rebuild clean

all: clean s21_matrix.a test gcov_report

s21_matrix.a:
	$(CC) $(CFLAGS) *.c -c
	ar rc s21_matrix.a *.o
	rm -rf *.o

test: clean s21_matrix.a
	$(CC) $(CFLAGS) tests/test.c -c
	$(CC) $(CFLAGS) tests/test.c *.c $(TFLAGS) -o test -L. s21_matrix.a
	./test

valgrind: clean s21_matrix.a
	$(CC) $(CFLAGS) tests/test.c -c
	$(CC) $(CFLAGS) tests/test.c *.c $(TFLAGS) -o test -L. s21_matrix.a
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./test

gcov_report: test
	lcov -t "s21_matrix" -o s21_matrix.info -c -d . 
	genhtml -o report s21_matrix.info

rebuild: clean test

clean:
	rm -rf *.gcno *.info *.gcda *.o *.a s21_matrix test report

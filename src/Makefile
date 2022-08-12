SRCS = s21_matrix_oop.cpp s21_help_funcs.cpp
	
OBJS = ${SRCS:.cpp=.o}
CC = g++
CFLAGS = -Wall -Werror -Wextra

all: clean s21_matrix_oop.a 

s21_matrix_oop.a: ${SRCS}
	${CC} ${CFLAGS} -std=c++20 -c ${SRCS}
	@libtool -static -o s21_matrix_oop.a ${OBJS}

test: s21_matrix_oop.a unit_test

unit_test:
	${CC} ${CFLAGS} -std=c++20 s21_matrix-test.cpp s21_matrix_oop.a -lgtest -lgtest_main -pthread -o test
	./test

gcov_report: s21_matrix_oop.a
	@g++ --coverage s21_matrix-test.cpp -lgtest ${SRCS} -o unit-test
	@./unit-test
	@lcov -t "test" -o test.info -c -d .
	@genhtml -o report test.info
	
clean:
	@/bin/rm -rf *.o *.a test unit-test *.gcno *gcda report *.info main *.out *.dSYM

checks: cppcheck leaks style

style:
	python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem . *.cpp

leaks: main.cpp
	CK_FORK=no leaks --atExit -- ./test
	
main: s21_matrix_oop.a main.cpp
	${CC} ${CFLAGS} -std=c++20 main.cpp s21_matrix_oop.a -o main

run: main
	./main

debug:
	${CC} ${CFLAGS} -std=c++20 -c ${SRCS} -g
	${CC} ${CFLAGS} -std=c++20 main.cpp s21_matrix_oop.a -o main -g
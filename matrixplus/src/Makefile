
SOURCE = matrix_oop.cc overloads.cc de_constructors.cc
TEST = test.cc
LIB = matrix_oop.a
GCOV = --coverage

OS = $(shell uname)

ifeq ($(OS), Darwin)
LIBFLAGS = -lm -lgtest -lstdc++
LEAKS = leaks --atExit -- test -fsanitize=address
else
LIBFLAGS = -lstdc++ `pkg-config --cflags --libs gtest`
LEAKS = CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all ./test
endif

all: clean test check gcov_report

test: test.cc
	$(GXX)  -std=c++17 $(SOURCE) test.cc $(LIBFLAGS) -o test 
	./test

matrix_oop.a: clean
	$(GXX) -c $(SOURCE)
	@ar rcs $(LIB) matrix_oop.o
	@ranlib $(LIB)

gcov_report: matrix_oop.a
	$(GXX) $(GCOV) $(TEST) matrix_oop.h $(SOURCE) $(LIB)  $(LIBFLAGS) -o test
	./test
	lcov -t "test" -c -d  ./ --no-external --output-file ./coverage.info
	genhtml ./coverage.info --output-directory ./report/

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config $(SOURCE) *.h
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n matrix_oop.cc test.cc matrix_oop.h overloads.cc de_constructors.cc
	$(GXX)  -std=c++17 $(SOURCE) test.cc $(LIBFLAGS) -o test 
	$(LEAKS)

clean:
	rm -rf *.o *.a *.so *.out *.dSYM test *.txt report *.info *.gcda *.gcno *.gch .clang-format
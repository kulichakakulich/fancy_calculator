CPP = g++
GCOV_TEST = gcov_report
TARGET = S21_SmartCalc
APP = build/S21_SmartCalc
GTEST = -lgtest
CFLAGS = -std=c++17 -Wall -Werror -Wextra -lstdc++
BUILDTARGET = s21_controller.cpp s21_model.cpp
TESTTARGET = test.cpp
FOLDER = SmartCalc/
LIBS = -lm -lpthread -D_GNU_SOURCE
GCOV = --coverage

all: clang-format $(TARGET)

$(TARGET):      
	mkdir $(FOLDER)
	cp S21_SmartCalc.pro *.h *.cpp *.ui *.h *.cpp *.ui $(FOLDER)
	cd $(FOLDER); qmake
	cd $(FOLDER); make
	cd $(FOLDER); rm -rf *.h *.cpp *.ui *.o *.pro *.qrc Makefile



install: $(TARGET)
	mkdir ../../SmartCalculator/
	cp -f $(FOLDER)/release/S21_SmartCalc.exe ../../SmartCalculator/
	


uninstall:
	rm -rf ../../SmartCalculator/

dvi:
	start documentation.html

dist: clean
	cd .. && tar -cf SmartCalculator.tar src && mv SmartCalculator.tar src


undist: clean
	rm -rf SmartCalculator.tar
	

test: clean
	$(CPP) $(CFLAGS) -c $(BUILDTARGET) $(LIBS)
	$(CPP) $(CFLAGS) $(LIBS) -c $(TESTTARGET) $(LIBS)
	$(CPP) $(CFLAGS) $(LIBS) *.o -o test $(GTEST)
	./test

clang:
	cp ../materials/linters/.clang-format . 
	clang-format -i *.cpp *.h
	clang-format -n *.cpp *.h; rm .clang-format
	
gcov_report: clean
	$(CPP) $(GCOV) $(CFLAGS) -c $(BUILDTARGET) $(LIBS)
	$(CPP) $(GCOV) $(CFLAGS) $(LIBS) -c $(TESTTARGET) $(LIBS)
	$(CPP) $(GCOV) $(CFLAGS) $(LIBS) *.o -o $(GCOV_TEST) -lgtest
	./$(GCOV_TEST)
	gcov $(TESTTARGET) -r
	lcov -t $(GCOV_TEST) -o $(GCOV_TEST).info --no-external -c -d .
	genhtml -o report $(GCOV_TEST).info
	rm -rf *.o *.a *.gc* *.info coveragcvge calc_test *.dSYM *.out gcov_report

leaks: clean test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./test -lm -lsubunit -lpthread -lrt

clean:	
	rm -Rf *.tar
	rm -rf test S21_SmartCalc gcov_report report
	rm -rf *.o *.so *.a fizz *.gc* *.info report *.out *.gcda *.so *.gcno *.info
	rm -rf SmartCalc/*.o SmartCalc/*.so SmartCalc/*.a SmartCalc/fizz SmartCalc/*.gc*
	rm -rf SmartCalc

.PHONY: all test gcov_report clean clang dvi dist install
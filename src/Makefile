CXX = g++ -ggdb3 -lstdc++ -Wall -Werror -Wextra 
GCOV = -fprofile-arcs -ftest-coverage
GCOF_FLAGS=lcov --no-external -t "gcov_report" -o gcov_report.info -c -d .
OS = $(shell uname)
ifeq ($(OS), Linux)
  LIBS = -lgtest -lstdc++  -lpthread -lrt -lm
  OPEN = xdg-open
  SOURCE_F = ./Build/SmartCalc_2
else
  LIBS = -lgtest -lstdc++ 
  OPEN = open
  SOURCE_F = ./Build/SmartCalc_2.app/Contents/MacOS/SmartCalc_2
endif

MANUAL_SRC = ./manual/index.html
BUILD = Build/
DEST = App/
TAR = SmartCalc_tar/
TEXI2HTML = makeinfo --html
TEST_FILES = smartCalc_test.cpp ./Model/model.cpp
CHECK_FILES  =./Model/*.h ./Model/*.cpp ./View/*.cpp ./View/*.h *.cpp ./Controller/*.h

all: gcov_report install

build:
	@qmake -o $(BUILD)/Makefile
	@make -C $(BUILD)

install: build dvi
	@mkdir $(DEST)
	@cp $(SOURCE_F) $(DEST)
	@cp $(MANUAL_SRC) $(DEST)
	@rm -rf $(BUILD)

uninstall:
	@rm -rf $(DEST)
	@rm -rf ./manual *.dSYM

dvi:
	@makeinfo --html manual.texi

dist: build
	@mkdir $(TAR)
	@tar -c -v -f ./$(TAR)SmartCalc_2.tar Build/ Makefile
	@rm -rf $(BUILD)

test: clean 
	@$(CXX) $(TEST_FILES) $(LIBS) -o smartCalc_test
	@./smartCalc_test

gcov_report: clean
	@$(CXX) $(GCOV) $(TEST_FILES) $(LIBS) -o gcov_report
	@./gcov_report
	@$(GCOF_FLAGS)
	@genhtml -o report gcov_report.info
	@$(OPEN) ./report/index.html


# ==================================================================================== #

clean:
	@rm -f *.o *.a *.gcno *.gcda *.info gcov_report *.out *.tar *.pdf *.dvi *.log s21_smartCalc_test 
	@rm -rf ./report *.dSYM ./SmartCalc_2_tar ./Build ./App
	@rm -rf ./manual *.dSYM

leaks: test
	@CK_FORK=no leaks --atExit -- ./s21_smartCalc_test
	@make clean

valgrind: test
	@valgrind --tool=memcheck --track-origins=yes --leak-check=full ./s21_smartCalc_test
	@make clean


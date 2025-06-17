CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
GFLAGS = -lm -lgtest -pthread
GAME = build/qt_games
BACK_LIB = backend.a
BACK_SRCS = brick_game/snake/backend_snake.cc brick_game/tetris/backend_tetris.cc
TEST_TARGET = tests/testing_exe
TEST_SRCS = tests/tests.cc
TEST_FLAGS = -fprofile-arcs -ftest-coverage
INFO = info/info.aux info/info.dvi info/info.log info/info.pdf

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	OPEN = xdg-open
else
	OPEN = open
endif

all: install

install: $(GAME)

$(GAME): uninstall $(BACK_LIB)
	@rm -rf build
	@mkdir build
	@cd build && cmake ..
	@cd build && make preinstall
	@rm -rf build/.qt build/Makefile build/CMakeFiles build/qt_games_autogen build/*.cmake build/*.txt
	@$(CC) $(CFLAGS) inc/console.cc gui/cli/frontend.cc -L. $(BACK_LIB) -o build/console_games -lncurses -lm
	@echo "┏====================================┓"
	@echo "┃  Games are installed successfully  ┃"
	@echo "┗====================================┛"

$(BACK_LIB):
	@$(CC) $(CFLAGS) -c brick_game/snake/backend_snake.cc -o snake.o
	@$(CC) $(CFLAGS) -c brick_game/tetris/backend_tetris.cc -o tetris.o
	@ar rcs $(BACK_LIB) *.o
	@rm -rf *.o

format_code:
	@echo "┏=========================================┓"
	@echo "┃  Formatting your code for Google Style  ┃"
	@echo "┗=========================================┛"
	@cp ../materials/linters/.clang-format .
	@clang-format -i brick_game/*.h brick_game/tetris/* brick_game/snake/* gui/cli/* gui/desktop/* inc/* tests/*.cc
	@rm -rf .clang-format

style_check:
	@echo "┏=======================================┓"
	@echo "┃  Checking your code for Google Style  ┃"
	@echo "┗=======================================┛"
	@cp ../materials/linters/.clang-format .
	@clang-format -n brick_game/*.h brick_game/tetris/* brick_game/snake/* gui/cli/* gui/desktop/* inc/*.cc tests/*.cc
	@rm -rf .clang-format

uninstall:
	@echo "┏=================┓"
	@echo "┃Games are deleted┃"
	@echo "┗=================┛"
	@rm -rf build

clean: uninstall
	@echo "Deleting unnescessary files"
	@rm -rf $(INFO) snake.tar build $(TEST_TARGET) coverage_report html latex $(BACK_LIB)

dvi:
	@doxygen info/Doxyfile
	@$(OPEN) html/index.html
	@latex info/info.tex
	@mv info.* info/
	@dvipdfmx info/info.dvi -o info/info.pdf
	@$(OPEN) info/info.pdf

dist: clean
	@tar -cvf snake.tar *
	@echo "┏=======================================┓"
	@echo "┃     Game archive has been created     ┃"
	@echo "┗=======================================┛"

test: $(TEST_TARGET)
	@./$(TEST_TARGET)

$(TEST_TARGET): $(BACK_LIB)
	@$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SRCS) -L. $(BACK_LIB) $(GFLAGS)

valgrind_check: $(TEST_TARGET)
	@CK_FORK=no valgrind --vgdb=no --leak-check=full \
	--show-leak-kinds=all --track-origins=yes -v --verbose -q --quiet -s $(TEST_TARGET)

gcov_report:
	@make clean
	@echo "┏====================================┓"
	@echo "┃     Generating your report ...     ┃"
	@echo "┗====================================┛"
	@$(CC) $(CFLAGS) $(TEST_FLAGS) -o $(TEST_TARGET) $(TEST_SRCS) $(BACK_SRCS) $(GFLAGS)
	@./$(TEST_TARGET)
	@gcov tests/testing_exe-backend_snake.gcda tests/testing_exe-backend_tetris.gcda
	@lcov --capture --directory . --output-file coverage.info --ignore-errors inconsistent --include "*/brick_game/snake/backend_snake.cc" --include "*/brick_game/tetris/backend_tetris.cc"
	@genhtml coverage.info --output-directory coverage_report
	@$(OPEN) coverage_report/index.html
	@rm -rf *.gcov tests/*.gcno tests/*.gcda $(TEST_TARGET) *.info

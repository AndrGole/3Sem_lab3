CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.
COV_FLAGS = --coverage
LDFLAGS = -lboost_unit_test_framework -lpthread -lgcov

PROGRAM = stack_program
TEST_PROGRAM = stack_tests
BENCH_PROGRAM = stack_bench
REPORT_DIR = coverage_report
LINT_FILES = Stack.h Stack.cpp interface.cpp test_stack.cpp bench_stack.cpp

.PHONY: all program test bench coverage lint clean

all: program

program: Stack.cpp interface.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(PROGRAM)

test: test_stack.cpp Stack.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(TEST_PROGRAM) $(LDFLAGS)
	./$(TEST_PROGRAM) --catch_system_errors=no

bench: bench_stack.cpp Stack.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(BENCH_PROGRAM) $(LDFLAGS)
	@echo "=== ЗАПУСК БЕНЧМАРКОВ STACK ==="
	./$(BENCH_PROGRAM) --catch_system_errors=no

coverage: clean_cov
	$(CXX) $(CXXFLAGS) $(COV_FLAGS) test_stack.cpp Stack.cpp -o $(TEST_PROGRAM)_cov $(LDFLAGS)
	@./$(TEST_PROGRAM)_cov --catch_system_errors=no 2>/dev/null || echo "Тесты завершены"
	@sleep 0.1
	@mkdir $(REPORT_DIR)
	@gcovr -r . --html --html-details --html-title "Coverage Report" --exclude-throw-branches -o $(REPORT_DIR)/index.html
	@echo " Отчёт: $(REPORT_DIR)/index.html"

lint:
	@echo "=== ПРОВЕРКА CLANG-TIDY ==="
	@if command -v clang-tidy >/dev/null 2>&1; then \
		for file in $(LINT_FILES); do \
			if [ -f "$$file" ]; then \
				echo "Анализ $$file..."; \
				clang-tidy $$file -- -std=c++17 $(CXXFLAGS); \
			fi; \
		done; \
	else \
		echo "clang-tidy не установлен."; \
	fi

lint-quick:
	@clang-tidy Stack.cpp --checks='-*,bugprone*,clang-analyzer*' -- -std=c++17 2>/dev/null || true

lint-std:
	@clang-tidy $(LINT_FILES) --checks='clang-analyzer-*,bugprone*,modernize*,performance*' -- -std=c++17

clean_cov:
	rm -f $(TEST_PROGRAM)_cov *.gcda *.gcno coverage.info $(BENCH_PROGRAM)
	rm -rf $(REPORT_DIR)

clean:
	rm -f $(PROGRAM) $(TEST_PROGRAM) $(BENCH_PROGRAM) $(TEST_PROGRAM)_cov *.gcda *.gcno coverage.info
	rm -rf $(REPORT_DIR) stack.txt stack.bin

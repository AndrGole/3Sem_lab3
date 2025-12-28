CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.
COV_FLAGS = --coverage
LDFLAGS = -lboost_unit_test_framework -lpthread -lgcov
BENCH_LDFLAGS = -lboost_unit_test_framework -lboost_chrono -lpthread -lgcov

PROGRAM = tree_program
TEST_PROGRAM = tree_tests
BENCH_PROGRAM = tree_bench
REPORT_DIR = coverage_report
LINT_FILES = Tree.h Tree.cpp Interface.cpp test_tree.cpp bench_tree.cpp

.PHONY: all program test bench coverage lint lint-quick lint-std clean_cov clean

all: program

program: Tree.cpp Interface.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(PROGRAM)

test: test_tree.cpp Tree.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(TEST_PROGRAM) $(LDFLAGS)
	@echo "=== ЗАПУСК ТЕСТОВ ==="
	./$(TEST_PROGRAM) --catch_system_errors=no

bench: bench_tree.cpp Tree.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(BENCH_PROGRAM) $(BENCH_LDFLAGS)
	@echo "=== ЗАПУСК БЕНЧМАРКОВ ==="
	./$(BENCH_PROGRAM) --catch_system_errors=no

coverage: clean_cov
	$(CXX) $(CXXFLAGS) $(COV_FLAGS) test_tree.cpp Tree.cpp -o $(TEST_PROGRAM)_cov $(LDFLAGS)
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
	@clang-tidy Tree.cpp --checks='-*,bugprone*,clang-analyzer*' -- -std=c++17 2>/dev/null || true

lint-std:
	@clang-tidy $(LINT_FILES) --checks='clang-analyzer-*,bugprone*,modernize*,performance*' -- -std=c++17

clean_cov:
	rm -f $(TEST_PROGRAM)_cov *.gcda *.gcno coverage.info $(BENCH_PROGRAM)
	rm -rf $(REPORT_DIR)

clean:
	rm -f $(PROGRAM) $(TEST_PROGRAM) $(BENCH_PROGRAM) $(TEST_PROGRAM)_cov *.gcda *.gcno coverage.info
	rm -rf $(REPORT_DIR) tree.txt tree.bin

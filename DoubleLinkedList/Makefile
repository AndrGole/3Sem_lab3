CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.
COV_FLAGS = --coverage
LDFLAGS = -lboost_unit_test_framework -lpthread -lgcov

PROGRAM = dlist_program
TEST_PROGRAM = dlist_tests
REPORT_DIR = coverage_report
LINT_FILES = DoubleLinked.h DoubleLinked.cpp interface.cpp test_dlist.cpp

.PHONY: all program test coverage lint clean

all: program

program: DoubleLinked.cpp interface.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(PROGRAM)

test: test_dlist.cpp DoubleLinked.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(TEST_PROGRAM) $(LDFLAGS)
	./$(TEST_PROGRAM) --catch_system_errors=no

bench: bench_dlist.cpp DoubleLinked.cpp
	$(CXX) $(CXXFLAGS) $^ -o dlist_bench $(LDFLAGS)
	@echo "=== ЗАПУСК БЕНЧМАРКОВ DOUBLELINKEDLIST ==="
	./dlist_bench --catch_system_errors=no

coverage: clean_cov
	$(CXX) $(CXXFLAGS) $(COV_FLAGS) test_dlist.cpp DoubleLinked.cpp -o $(TEST_PROGRAM)_cov $(LDFLAGS)
	@./$(TEST_PROGRAM)_cov --catch_system_errors=no >/dev/null 2>&1 || echo "Тесты завершены (возможны ошибки)"
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
				clang-tidy $$file -- -x c++ -std=c++17 $(CXXFLAGS); \
			fi; \
		done; \
	else \
		echo "clang-tidy не установлен."; \
	fi

clean_cov:
	rm -f $(TEST_PROGRAM)_cov *.gcda *.gcno coverage.info
	rm -rf $(REPORT_DIR)

clean:
	rm -f $(PROGRAM) $(TEST_PROGRAM) $(TEST_PROGRAM)_cov *.gcda *.gcno coverage.info
	rm -rf $(REPORT_DIR) dlist.txt

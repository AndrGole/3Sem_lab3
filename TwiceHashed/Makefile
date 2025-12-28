CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.
LDFLAGS = -lboost_unit_test_framework -lpthread -lgcov
BENCH_LDFLAGS = -lboost_unit_test_framework -lboost_chrono -lpthread -lgcov
COV_FLAGS = --coverage

PROGRAM = hash_program
TEST_PROGRAM = hash_tests
BENCH_PROGRAM = hash_bench
REPORT_DIR = coverage_report

all: program

program: HashTable.cpp Interface.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(PROGRAM)

test: test_hash.cpp HashTable.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(TEST_PROGRAM) $(LDFLAGS)
	@echo "=== ЗАПУСК ТЕСТОВ ==="
	./$(TEST_PROGRAM)

bench: bench_hash.cpp HashTable.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(BENCH_PROGRAM) $(BENCH_LDFLAGS)
	@echo "=== ЗАПУСК БЕНЧМАРКОВ ==="
	./$(BENCH_PROGRAM)

coverage: clean_cov
	$(CXX) $(CXXFLAGS) $(COV_FLAGS) test_hash.cpp HashTable.cpp -o $(TEST_PROGRAM)_cov $(LDFLAGS)
	./$(TEST_PROGRAM)_cov
	@sleep 0.1
	@mkdir $(REPORT_DIR)
	@gcovr -r . --html --html-details --html-title "Coverage Report" --exclude-throw-branches -o $(REPORT_DIR)/index.html
	@echo " Отчёт: $(REPORT_DIR)/index.html"

lint:
	@echo "=== CLANG-TIDY ==="
	clang-tidy HashTable.cpp HashTable.h Interface.cpp test_hash.cpp bench_hash.cpp -- -std=c++17 $(CXXFLAGS)

clean_cov:
	rm -f $(TEST_PROGRAM)_cov *.gcda *.gcno coverage.info
	rm -rf $(REPORT_DIR)

clean:
	rm -f $(PROGRAM) $(TEST_PROGRAM) $(BENCH_PROGRAM) $(TEST_PROGRAM)_cov *.gcda *.gcno coverage.info
	rm -rf $(REPORT_DIR) hashtable.txt hashtable.bin

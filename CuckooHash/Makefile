CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.
LDFLAGS = -lboost_unit_test_framework -lpthread  -lgcov
BENCH_LDFLAGS = -lboost_unit_test_framework -lboost_chrono -lpthread  -lgcov
COV_FLAGS = --coverage

PROGRAM = cuckoo_program
TEST_PROGRAM = cuckoo_tests
BENCH_PROGRAM = cuckoo_bench
REPORT_DIR = coverage_report

all: program

program: CuckooHash.cpp Interface.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(PROGRAM)

test: test_cuckoo.cpp CuckooHash.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(TEST_PROGRAM) $(LDFLAGS)
	@echo "=== ЗАПУСК ТЕСТОВ КУКУШКИНОГО ХЭШИРОВАНИЯ ==="
	./$(TEST_PROGRAM)

bench: bench_cuckoo.cpp CuckooHash.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(BENCH_PROGRAM) $(BENCH_LDFLAGS)
	@echo "=== ЗАПУСК БЕНЧМАРКОВ КУКУШКИНОГО ХЭШИРОВАНИЯ ==="
	./$(BENCH_PROGRAM)

coverage: clean_cov
	$(CXX) $(CXXFLAGS) $(COV_FLAGS) test_cuckoo.cpp CuckooHash.cpp -o $(TEST_PROGRAM)_cov $(LDFLAGS)
	./$(TEST_PROGRAM)_cov
	@sleep 0.1
	@mkdir $(REPORT_DIR)
	@gcovr -r . --html --html-details --html-title "Coverage Report" --exclude-throw-branches -o $(REPORT_DIR)/index.html
	@echo " Отчёт: $(REPORT_DIR)/index.html"

lint:
	clang-tidy CuckooHash.cpp CuckooHash.h Interface.cpp test_cuckoo.cpp bench_cuckoo.cpp -- -std=c++17 $(CXXFLAGS)

clean_cov:
	rm -f $(TEST_PROGRAM)_cov *.gcda *.gcno coverage.info
	rm -rf $(REPORT_DIR)

clean:
	rm -f $(PROGRAM) $(TEST_PROGRAM) $(BENCH_PROGRAM) $(TEST_PROGRAM)_cov *.gcda *.gcno coverage.info
	rm -rf $(REPORT_DIR) cuckoo.txt cuckoo.bin

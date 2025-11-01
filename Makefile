CXX = g++-15
CXXFLAGS = -std=c++20 -Wall -Wextra -O2
TEST_DIR = tests
BIN_DIR = $(TEST_DIR)/bin

# Find all test files
TEST_SOURCES = $(shell find $(TEST_DIR) -name 'test_*.cpp')
TEST_BINARIES = $(patsubst $(TEST_DIR)/%.cpp,$(BIN_DIR)/%,$(TEST_SOURCES))

# Default target
.PHONY: all
all: test

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Pattern rule to compile test files
$(BIN_DIR)/%: $(TEST_DIR)/%.cpp | $(BIN_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

# Run all tests
.PHONY: test
test: $(TEST_BINARIES)
	@./run_tests.sh $(TEST_BINARIES)

# Clean compiled test binaries
.PHONY: clean
clean:
	rm -rf $(BIN_DIR)

# Help target
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  make test       - Compile and run all tests"
	@echo "  make clean      - Remove compiled test binaries"
	@echo "  make help       - Show this help message"


#!/bin/bash

# Test runner script for contestlib
# Usage: ./run_tests.sh [test_binary1] [test_binary2] ...

if [ $# -eq 0 ]; then
    echo "No tests to run."
    exit 0
fi

echo "Running all tests..."

passed=0
failed=0
failed_tests=()

for test in "$@"; do
    echo ""
    echo "Running $test..."
    if "$test"; then
        passed=$((passed + 1))
    else
        failed=$((failed + 1))
        failed_tests+=("$test")
    fi
done

echo ""
echo "========================================"
echo "Test Results: $passed passed, $failed failed"
echo "========================================"

if [ $failed -gt 0 ]; then
    echo ""
    echo "Failed tests:"
    for test in "${failed_tests[@]}"; do
        echo "  - $test"
    done
    exit 1
fi

exit 0


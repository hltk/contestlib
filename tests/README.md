# Test Framework

This directory contains tests for all implementations in the contestlib repository. The test framework is designed to verify correctness through comprehensive test cases.

## Testing Philosophy

### 1. Test All Small Corner Cases
Every implementation should be tested against small edge cases and boundary conditions:
- Empty inputs
- Single element cases
- Minimum and maximum constraints
- Special values (0, 1, -1, etc.)
- Edge cases specific to the algorithm

### 2. Fuzzy Testing with Random Small Cases
When applicable, use randomized testing to verify correctness:
- Generate small random test cases
- Solve them using a naive/brute-force approach
- Compare with the optimized implementation
- This helps catch bugs that might not be obvious in handwritten test cases

## Directory Structure

Tests are organized to mirror the source code structure:

```
tests/
├── datastruct/     # Data structure tests
├── graph/          # Graph algorithm tests
├── math/           # Math utility tests
├── misc/           # Miscellaneous utility tests
├── string/         # String algorithm tests
└── bin/            # Compiled test binaries (ignored by git)
```

## Running Tests

### Run All Tests
```bash
make test
```

This compiles all test files and runs them, reporting a summary of passed/failed tests.

### Run Individual Test
```bash
make test-dsu
```

Replace `dsu` with the name of any implementation.

### Clean Compiled Binaries
```bash
make clean
```

## Writing Tests

### File Naming Convention
- Test files must be named `test_*.cpp`
- Place them in the appropriate subdirectory (e.g., `tests/datastruct/test_dsu.cpp`)

### Basic Test Structure

```cpp
#include "../../datastruct/implementation.cpp"
#include <cassert>
#include <iostream>

int main() {
    // Test 1: Corner cases
    {
        // Empty case
        // Single element
        // Boundary values
    }
    
    // Test 2: Small examples
    {
        // Known correct examples
    }
    
    // Test 3: Fuzzy testing (if applicable)
    {
        // Generate random small inputs
        // Compare with brute force solution
    }
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
```

### Example: DSU Test

See `tests/datastruct/test_dsu.cpp` for a comprehensive example that includes:
- Basic operations (merge, same)
- Size tracking
- Multiple components
- Edge cases (merging already connected nodes)
- Stress testing (long chains, star topology)

### Fuzzy Testing Example

When writing fuzzy tests, follow this pattern:

```cpp
// Example: Testing a range query data structure
#include <random>
#include <vector>

// Naive solution for verification
int naive_query(const std::vector<int>& arr, int l, int r) {
    int result = /* compute naively */;
    return result;
}

void fuzzy_test() {
    std::mt19937 rng(42);  // Fixed seed for reproducibility
    
    for (int test = 0; test < 100; test++) {
        int n = 1 + rng() % 20;  // Small random size
        std::vector<int> arr(n);
        
        for (int& x : arr) {
            x = rng() % 100;  // Random values
        }
        
        DataStructure ds(arr);
        
        // Test random queries
        for (int q = 0; q < 10; q++) {
            int l = rng() % n;
            int r = l + rng() % (n - l);
            
            assert(ds.query(l, r) == naive_query(arr, l, r));
        }
    }
}
```

## Best Practices

### 1. Use Assertions
Use `assert()` for test conditions. They provide clear failure points and line numbers.

```cpp
assert(dsu.same(0, 1));  // Clear failure if false
```

### 2. Test Incrementally
Start with simple cases and gradually increase complexity:
1. Empty/single element
2. Small fixed examples
3. Larger structured cases
4. Random fuzzy tests

### 3. Use Fixed Random Seeds
When doing fuzzy testing, use a fixed seed for reproducibility:
```cpp
std::mt19937 rng(42);  // Same results every run
```

### 4. Keep Tests Small and Fast
- Fuzzy tests should use small inputs (n ≤ 100 typically)
- Tests should complete in under 1 second
- Focus on correctness, not performance

### 5. Test Edge Cases First
Common edge cases to consider:
- Empty inputs
- Single element
- All elements the same
- Already sorted/reverse sorted
- Maximum/minimum values
- Powers of 2 (for tree structures)

### 6. Document Tricky Test Cases
Add comments explaining non-obvious test cases:
```cpp
// Test path compression: create long chain, then query
// This verifies that root() properly compresses paths
```

### 7. Separate Test Sections
Group related tests together with clear comments:
```cpp
// Test 1: Basic operations
{ /* ... */ }

// Test 2: Edge cases
{ /* ... */ }

// Test 3: Fuzzy testing
{ /* ... */ }
```

## Adding New Tests

1. Read the implementation to understand its API and edge cases
2. Create `test_<name>.cpp` in the appropriate directory
3. Write corner case tests first
4. Add small example tests with known outputs
5. If applicable, add fuzzy tests comparing to naive solution
6. Run `make test` to verify
7. Update the checklist in the main `TODO` file

## Debugging Failed Tests

When a test fails:
1. Check the assertion line number
2. Add print statements before the assertion to see values
3. Reduce the test case to the minimal failing example
4. Fix the implementation or test as needed

Example debugging:
```cpp
// Add before failing assertion:
std::cout << "Expected: " << expected << ", Got: " << actual << std::endl;
assert(expected == actual);
```

## Current Test Status

See the main repository `TODO` file for a checklist of all tests that need to be written.

Completed tests:
- ✅ `datastruct/test_dsu.cpp`

Remaining tests: See `TODO` file in repository root.


# contestlib

A collection of competitive programming templates and algorithms in C++.

## Repository Structure

### Data Structures (`datastruct/`)

- **`dsu.cpp`**: Disjoint Set Union (Union-Find) with path compression and union by size
- **`fen.cpp`**: Fenwick Tree (Binary Indexed Tree) for prefix sum queries
- **`hasher.cpp`**: String hashing utilities
- **`indexed_set.cpp`**: Ordered set with index-based queries
- **`lazy_seg_tree.cpp`**: Segment tree with lazy propagation
- **`lichao.cpp`**: Li Chao tree for maintaining convex hull of lines
- **`linear_rmq.cpp`**: Linear-time RMQ preprocessing
- **`monotonic_queue.cpp`**: Monotonic queue for sliding window problems
- **`rmq.cpp`**: Range Minimum Query with sparse table
- **`seg_tree.cpp`**: Standard segment tree implementation
- **`short_lazy_seg_tree.cpp`**: Compact lazy segment tree
- **`short_rmq.cpp`**: Compact RMQ implementation
- **`treap.cpp`**: Treap (randomized binary search tree)

### Graph Algorithms (`graph/`)

- **`binary_lifting_lca.cpp`**: Lowest Common Ancestor using binary lifting
- **`centroid.cpp`**: Centroid decomposition
- **`dijkstra.cpp`**: Dijkstra's shortest path algorithm
- **`dinic.cpp`**: Dinic's algorithm for maximum flow
- **`hld.cpp`**: Heavy-Light Decomposition
- **`lca.cpp`**: Lowest Common Ancestor
- **`linear_lca.cpp`**: Linear-time LCA preprocessing

### Math (`math/`)

- **`fact.cpp`**: Factorial and combinatorics utilities
- **`mod_int.cpp`**: Modular arithmetic with automatic modulo operations

### String Algorithms (`string/`)

- **`aho_corasick.cpp`**: Aho-Corasick automaton for multi-pattern matching
- **`kmp.cpp`**: KMP (Knuth-Morris-Pratt) pattern matching algorithm

### Miscellaneous (`misc/`)

- **`bins.cpp`**: Binary search utilities
- **`compress_inplace.cpp`**: In-place coordinate compression
- **`compress.cpp`**: Coordinate compression
- **`fast_input.cpp`**: Fast I/O for competitive programming
- **`rand.cpp`**: Random number generation utilities
- **`timer.cpp`**: Timing and benchmarking utilities
- **`vec.cpp`**: Vector utilities and shortcuts

## Usage

Each file is a self-contained implementation that can be copied directly into your solution. Most implementations use templates or classes for flexibility.

### Example: Using DSU

```cpp
DSU dsu(n);  // Initialize with n elements
dsu.merge(u, v);  // Union operation
bool connected = dsu.same(u, v);  // Check if in same set
int sz = dsu.size(u);  // Get size of component
```

### Example: Using Dijkstra

```cpp
Dijkstra<ll> dij(n);  // Initialize with n nodes
dij.addedge(u, v, w);  // Add edge from u to v with weight w
auto dist = dij.run(source);  // Run from source, returns distance vector
auto path = dij.get_path(target);  // Get shortest path to target
```

### Example: Using ModInt

```cpp
using mint = ModInt<1000000007>;
mint a = 5, b = 3;
mint c = a * b + a / b;  // Automatic modular arithmetic
cout << c << endl;
```

### Example: Using KMP

```cpp
KMP kmp("pattern");  // Initialize with pattern
auto matches = kmp.find_all("text with pattern");  // Find all occurrences
bool found = kmp.exists("text");  // Check if pattern exists
int count = kmp.count("text");  // Count occurrences
```

## Coding Style

See [STYLE.md](STYLE.md) for detailed information about the coding conventions used in this library.

## Testing

This repository includes a test framework to verify the correctness of implementations.

### Running Tests

To run all tests:

```bash
make test
```

To run a specific test (e.g., DSU):

```bash
make test-dsu
```

To clean compiled test binaries:

```bash
make clean
```

### Adding New Tests

1. Create a test file in the appropriate subdirectory of `tests/` following the naming convention `test_*.cpp`
2. Include the implementation file using a relative path (e.g., `#include "../../datastruct/dsu.cpp"`)
3. Write test cases using assertions
4. The test will automatically be discovered and compiled by the Makefile

Example test structure:

```cpp
#include "../../datastruct/dsu.cpp"
#include <cassert>
#include <iostream>

int main() {
    // Test case 1
    DSU dsu(5);
    assert(!dsu.same(0, 1));
    dsu.merge(0, 1);
    assert(dsu.same(0, 1));

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
```

## Contributing

This is a personal competitive programming library. Feel free to use these implementations in your own contests or as reference material.

## License

This code is intended for competitive programming use.

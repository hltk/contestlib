# contestlib

A collection of competitive programming templates and algorithms in C++.

## Repository Structure

### Data Structures (`datastruct/`)

- **`dsu.cpp`**: Disjoint Set Union (Union-Find) with path compression and union by size
- **`fen.cpp`**: Fenwick Tree (Binary Indexed Tree) for prefix sum queries
- **`hasher.cpp`**: String hashing utilities
- **`indexed_set.cpp`**: Ordered set with index-based queries
- **`lazysegtree.cpp`**: Segment tree with lazy propagation
- **`lichao.cpp`**: Li Chao tree for maintaining convex hull of lines
- **`linear_rmq.cpp`**: Linear-time RMQ preprocessing
- **`monotonicqueue.cpp`**: Monotonic queue for sliding window problems
- **`rmq.cpp`**: Range Minimum Query with sparse table
- **`segtree.cpp`**: Standard segment tree implementation
- **`shortlazysegtree.cpp`**: Compact lazy segment tree
- **`shortrmq.cpp`**: Compact RMQ implementation
- **`treap.cpp`**: Treap (randomized binary search tree)

### Graph Algorithms (`graph/`)

- **`binary_lifting_lca.cpp`**: Lowest Common Ancestor using binary lifting
- **`centroid.cpp`**: Centroid decomposition
- **`dinic.cpp`**: Dinic's algorithm for maximum flow
- **`hld.cpp`**: Heavy-Light Decomposition
- **`lca.cpp`**: Lowest Common Ancestor
- **`linear_lca.cpp`**: Linear-time LCA preprocessing

### Math (`math/`)

- **`fact.cpp`**: Factorial and combinatorics utilities
- **`modint.cpp`**: Modular arithmetic with automatic modulo operations

### String Algorithms (`string/`)

- **`aho-corasick.cpp`**: Aho-Corasick automaton for multi-pattern matching
- **`old-aho-corasick.cpp`**: Previous implementation (kept for reference)

### Miscellaneous (`misc/`)

- **`bins.cpp`**: Binary search utilities
- **`compress_inplace.cpp`**: In-place coordinate compression
- **`compress.cpp`**: Coordinate compression
- **`fastinput.cpp`**: Fast I/O for competitive programming
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

### Example: Using ModInt

```cpp
using mint = ModInt<1000000007>;
mint a = 5, b = 3;
mint c = a * b + a / b;  // Automatic modular arithmetic
cout << c << endl;
```

## Contributing

This is a personal competitive programming library. Feel free to use these implementations in your own contests or as reference material.

## License

This code is intended for competitive programming use.

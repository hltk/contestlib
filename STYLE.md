# Coding Style

This library follows consistent coding conventions optimized for competitive programming. Understanding these patterns helps when reading, using, or extending the code.

## Naming Conventions

- **Structs**: PascalCase (`DSU`, `Tree`, `ModInt`, `LCA`, `FenTree`, `AhoCorasick`, `Treap`, `Dinic`, `HLD`)
- **Functions/Methods**: snake_case (`root`, `same`, `merge`, `query`, `add_word`, `dfs_sz`, `push`, `pull`)
- **Variables**: snake_case, often abbreviated for brevity (`f`, `siz`, `n`, `g`, `v`, `w`, `par`, `sz`, `jmp`, `in`)
- **Template Parameters**:
  - Type parameters: Single uppercase letter or PascalCase (`T`, `MC`)
  - Non-type parameters: Uppercase (`MOD`, `AS`)
- **Type Aliases**: snake_case with standard abbreviations (`ll`, `vi`, `mint`, `graph`)

## Structs vs Classes

- **Always use structs**: All data structures use `struct`, never `class`
- **No access specifiers**: Members are naturally public by default; no `public:` or `private:` keywords
- **Member ordering**: Implementation details and helper functions come first, followed by the primary public interface

## Code Organization

- **Self-contained**: Each file can be copied directly into a solution without dependencies (except for explicit includes)

## Formatting

- **Indentation**: Tabs are used consistently throughout
- **Bracing**: K&R style (opening brace on the same line)
- **Density**: Code is compact and optimized for quick reading during contests
- **Namespace**: `using namespace std;` is standard practice

## Comments

- **Source attribution**: Credits original authors or sources (e.g., `// source: kactl`, `// source: ecnerwala, own, Benq`)
- **Algorithm details**: Brief functional comments where algorithms need clarification
- **Parameter conventions**: Documents range types (e.g., `// [a, b)` for half-open intervals, `// half-open interval!`)

## Modern C++ Features

The library makes extensive use of modern C++ (C++17/C++20) features:

- **Structured bindings**: `auto [l, r] = minmax(time[a], time[b]);`
- **Range-based for loops**: `for (auto& u : g[s])`
- **Type inference**: Liberal use of `auto` keyword
- **Template metaprogramming**: `std::enable_if_t`, `std::is_integral_v` for SFINAE
- **Lambda functions**: Used as parameters for generic operations

## Template Usage

- **Generic implementations**: Heavy use of templates for flexibility and reusability
- **Default parameters**: Template parameters often have sensible defaults (e.g., `template<char MC = 'a', int AS = 26>`)
- **Type flexibility**: Data structures work with any compatible types

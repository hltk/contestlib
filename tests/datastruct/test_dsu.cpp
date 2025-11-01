#include "../../datastruct/dsu.cpp"
#include <cassert>
#include <iostream>

int main() {
	// Test 1: Basic operations
	{
		DSU dsu(5);
		assert(!dsu.same(0, 1));
		assert(!dsu.same(2, 3));
		
		dsu.merge(0, 1);
		assert(dsu.same(0, 1));
		assert(!dsu.same(0, 2));
	}

	// Test 2: Size tracking
	{
		DSU dsu(10);
		assert(dsu.size(0) == 1);
		
		dsu.merge(0, 1);
		assert(dsu.size(0) == 2);
		assert(dsu.size(1) == 2);
		
		dsu.merge(2, 3);
		dsu.merge(0, 2);
		assert(dsu.size(0) == 4);
		assert(dsu.size(1) == 4);
		assert(dsu.size(2) == 4);
		assert(dsu.size(3) == 4);
	}

	// Test 3: Multiple components
	{
		DSU dsu(8);
		dsu.merge(0, 1);
		dsu.merge(1, 2);
		dsu.merge(3, 4);
		dsu.merge(5, 6);
		
		assert(dsu.same(0, 2));
		assert(dsu.same(3, 4));
		assert(dsu.same(5, 6));
		assert(!dsu.same(0, 3));
		assert(!dsu.same(0, 5));
		assert(!dsu.same(3, 5));
		
		assert(dsu.size(0) == 3);
		assert(dsu.size(3) == 2);
		assert(dsu.size(5) == 2);
		assert(dsu.size(7) == 1);
	}

	// Test 4: Merging already connected components
	{
		DSU dsu(5);
		dsu.merge(0, 1);
		dsu.merge(1, 2);
		
		assert(dsu.merge(0, 1) == false);  // Already connected
		assert(dsu.merge(2, 0) == false);  // Already connected
		assert(dsu.size(0) == 3);
	}

	// Test 5: Chain merges
	{
		DSU dsu(10);
		for (int i = 0; i < 9; i++) {
			dsu.merge(i, i + 1);
		}
		
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				assert(dsu.same(i, j));
			}
			assert(dsu.size(i) == 10);
		}
	}

	// Test 6: Star topology
	{
		DSU dsu(10);
		for (int i = 1; i < 10; i++) {
			dsu.merge(0, i);
		}
		
		for (int i = 0; i < 10; i++) {
			assert(dsu.size(i) == 10);
		}
		
		for (int i = 1; i < 10; i++) {
			for (int j = i + 1; j < 10; j++) {
				assert(dsu.same(i, j));
			}
		}
	}

	// Test 7: Path compression verification
	{
		DSU dsu(100);
		// Create a long chain
		for (int i = 0; i < 99; i++) {
			dsu.merge(i, i + 1);
		}
		
		// All should be in same component
		for (int i = 0; i < 100; i++) {
			assert(dsu.same(0, i));
			assert(dsu.size(i) == 100);
		}
	}

	std::cout << "All DSU tests passed!" << std::endl;
	return 0;
}


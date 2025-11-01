#include "../../datastruct/fen.cpp"
#include <cassert>
#include <iostream>

using namespace std;

int main() {
	// Test 1: Basic updates and queries
	{
		FenTree<int> fen(10);
		fen.update(0, 5);
		fen.update(1, 3);
		fen.update(2, 7);
		
		assert(fen.query(1) == 5);    // [0, 1)
		assert(fen.query(2) == 8);    // [0, 2)
		assert(fen.query(3) == 15);   // [0, 3)
	}

	// Test 2: Range sum
	{
		FenTree<int> fen(10);
		for (int i = 0; i < 5; ++i) {
			fen.update(i, i + 1);  // 1, 2, 3, 4, 5
		}
		
		assert(fen.query(5) == 15);  // 1+2+3+4+5
		assert(fen.query(3) == 6);   // 1+2+3
		
		// Range [2, 5) = query(5) - query(2)
		int range_sum = fen.query(5) - fen.query(2);
		assert(range_sum == 12);  // 3+4+5
	}

	// Test 3: Multiple updates to same position
	{
		FenTree<int> fen(5);
		fen.update(2, 10);
		fen.update(2, 5);
		fen.update(2, -3);
		
		assert(fen.query(3) == 12);  // 10+5-3
	}

	// Test 4: All zeros
	{
		FenTree<int> fen(10);
		for (int i = 0; i < 10; ++i) {
			assert(fen.query(i) == 0);
		}
	}

	// Test 5: Negative values
	{
		FenTree<int> fen(5);
		fen.update(0, 10);
		fen.update(1, -5);
		fen.update(2, 3);
		
		assert(fen.query(1) == 10);
		assert(fen.query(2) == 5);   // 10 - 5
		assert(fen.query(3) == 8);   // 10 - 5 + 3
	}

	// Test 6: Lower bound - find first position where sum >= target
	{
		FenTree<int> fen(10);
		fen.update(0, 5);
		fen.update(1, 3);
		fen.update(2, 7);
		fen.update(3, 2);
		
		// Cumulative: [5, 8, 15, 17, ...]
		assert(fen.lower_bound(1) == 0);   // sum >= 1 at pos 0
		assert(fen.lower_bound(5) == 0);   // sum >= 5 at pos 0
		assert(fen.lower_bound(6) == 1);   // sum >= 6 at pos 1 (5+3=8)
		assert(fen.lower_bound(10) == 2);  // sum >= 10 at pos 2 (5+3+7=15)
		assert(fen.lower_bound(16) == 3);  // sum >= 16 at pos 3 (5+3+7+2=17)
	}

	// Test 7: Lower bound edge cases
	{
		FenTree<int> fen(5);
		fen.update(0, 10);
		
		assert(fen.lower_bound(0) == -1);   // Empty sum satisfies
		assert(fen.lower_bound(-5) == -1);  // Negative sum
		assert(fen.lower_bound(10) == 0);   // Exact match
		assert(fen.lower_bound(11) == 5);   // Beyond first element, no position has sum >= 11 with only one element
	}

	// Test 8: Single element
	{
		FenTree<int> fen(1);
		fen.update(0, 42);
		
		assert(fen.query(1) == 42);
		assert(fen.lower_bound(42) == 0);
		assert(fen.lower_bound(43) == 1);
	}

	// Test 9: Large tree
	{
		FenTree<int> fen(1000);
		for (int i = 0; i < 1000; ++i) {
			fen.update(i, 1);
		}
		
		assert(fen.query(100) == 100);
		assert(fen.query(500) == 500);
		assert(fen.query(1000) == 1000);
	}

	// Test 10: Incremental updates
	{
		FenTree<int> fen(10);
		
		for (int i = 0; i < 5; ++i) {
			fen.update(i, 2);
		}
		
		assert(fen.query(5) == 10);
		
		// Update more
		for (int i = 5; i < 10; ++i) {
			fen.update(i, 3);
		}
		
		assert(fen.query(10) == 25);  // 5*2 + 5*3
	}

	// Test 11: With long long
	{
		FenTree<long long> fen(5);
		fen.update(0, 1000000000LL);
		fen.update(1, 1000000000LL);
		
		assert(fen.query(2) == 2000000000LL);
	}

	// Test 12: Query at boundaries
	{
		FenTree<int> fen(5);
		for (int i = 0; i < 5; ++i) {
			fen.update(i, i + 1);
		}
		
		assert(fen.query(0) == 0);   // Empty range
		assert(fen.query(1) == 1);
		assert(fen.query(5) == 15);  // Full range
	}

	// Test 13: Subtract updates
	{
		FenTree<int> fen(5);
		fen.update(0, 100);
		fen.update(0, -30);
		
		assert(fen.query(1) == 70);
	}

	// Test 14: Point query using range
	{
		FenTree<int> fen(10);
		fen.update(5, 42);
		
		// Point query at 5: query(6) - query(5)
		int point_val = fen.query(6) - fen.query(5);
		assert(point_val == 42);
	}

	// Test 15: Lower bound with all same values
	{
		FenTree<int> fen(10);
		for (int i = 0; i < 10; ++i) {
			fen.update(i, 5);
		}
		
		// Cumulative: [5, 10, 15, 20, ...]
		assert(fen.lower_bound(1) == 0);
		assert(fen.lower_bound(8) == 1);
		assert(fen.lower_bound(25) == 4);
		assert(fen.lower_bound(50) == 9);
		assert(fen.lower_bound(51) == 10);  // Beyond all elements
	}

	cout << "All Fenwick tree tests passed!" << endl;
	return 0;
}

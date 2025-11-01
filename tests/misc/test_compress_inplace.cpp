#include "../../misc/compress_inplace.cpp"
#include <cassert>
#include <iostream>

using namespace std;

int main() {
	// Test 1: Simple sequence with duplicates
	{
		vector<int> v = {5, 2, 8, 2, 1};
		compress(v);
		// Sorted values: [1, 2, 2, 5, 8]
		// Ranks: 1->0, 2->1, 5->2, 8->3
		// Original positions: 5->2, 2->1, 8->3, 2->1, 1->0
		vector<int> expected = {2, 1, 3, 1, 0};
		assert(v == expected);
	}

	// Test 2: Already sorted
	{
		vector<int> v = {1, 2, 3, 4, 5};
		compress(v);
		vector<int> expected = {0, 1, 2, 3, 4};
		assert(v == expected);
	}

	// Test 3: Reverse sorted
	{
		vector<int> v = {5, 4, 3, 2, 1};
		compress(v);
		// Ranks: 1->0, 2->1, 3->2, 4->3, 5->4
		vector<int> expected = {4, 3, 2, 1, 0};
		assert(v == expected);
	}

	// Test 4: All same elements
	{
		vector<int> v = {7, 7, 7, 7};
		compress(v);
		vector<int> expected = {0, 0, 0, 0};  // All get rank 0
		assert(v == expected);
	}

	// Test 5: Single element
	{
		vector<int> v = {42};
		compress(v);
		vector<int> expected = {0};
		assert(v == expected);
	}

	// Test 6: Two elements - different
	{
		vector<int> v = {10, 5};
		compress(v);
		// Ranks: 5->0, 10->1
		vector<int> expected = {1, 0};
		assert(v == expected);
	}

	// Test 7: Two elements - same
	{
		vector<int> v = {5, 5};
		compress(v);
		vector<int> expected = {0, 0};
		assert(v == expected);
	}

	// Test 8: Multiple groups of duplicates
	{
		vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5};
		compress(v);
		// Unique sorted: 1, 2, 3, 4, 5, 6, 9
		// Ranks: 1->0, 2->1, 3->2, 4->3, 5->4, 6->5, 9->6
		vector<int> expected = {2, 0, 3, 0, 4, 6, 1, 5, 4};
		assert(v == expected);
	}

	// Test 9: Negative numbers
	{
		vector<int> v = {-5, 0, -10, 5, -2};
		compress(v);
		// Unique sorted: -10, -5, -2, 0, 5
		// Ranks: -10->0, -5->1, -2->2, 0->3, 5->4
		vector<int> expected = {1, 3, 0, 4, 2};
		assert(v == expected);
	}

	// Test 10: Large values
	{
		vector<int> v = {1000000, 1, 999999, 2, 1};
		compress(v);
		// Unique sorted: 1, 2, 999999, 1000000
		// Ranks: 1->0, 2->1, 999999->2, 1000000->3
		vector<int> expected = {3, 0, 2, 1, 0};
		assert(v == expected);
	}

	// Test 11: Check that duplicates get same rank
	{
		vector<int> v = {100, 50, 100, 50, 100};
		compress(v);
		// Ranks: 50->0, 100->1
		vector<int> expected = {1, 0, 1, 0, 1};
		assert(v == expected);
	}

	// Test 12: Sequence with gaps
	{
		vector<int> v = {1, 10, 100, 1000};
		compress(v);
		// Even with gaps, ranks are consecutive
		vector<int> expected = {0, 1, 2, 3};
		assert(v == expected);
	}

	// Test 13: Many duplicates
	{
		vector<int> v = {5, 5, 5, 3, 3, 1};
		compress(v);
		// Ranks: 1->0, 3->1, 5->2
		vector<int> expected = {2, 2, 2, 1, 1, 0};
		assert(v == expected);
	}

	// Test 14: With chars
	{
		vector<char> v = {'d', 'b', 'd', 'a', 'b'};
		compress(v);
		// Ranks: 'a'->0, 'b'->1, 'd'->2
		vector<char> expected = {2, 1, 2, 0, 1};
		assert(v == expected);
	}

	// Test 15: Verify ranks are 0-indexed and consecutive
	{
		vector<int> v = {42, 17, 99, 17, 5, 42};
		compress(v);
		// Ranks: 5->0, 17->1, 42->2, 99->3
		// Check all values are in [0, 3]
		for (int x : v) {
			assert(x >= 0 && x <= 3);
		}
		// Check 17 and 42 have same ranks
		assert(v[1] == v[3]);  // both were 17
		assert(v[0] == v[5]);  // both were 42
		// Check they're different ranks
		assert(v[0] != v[1]);
	}

	// Test 16: Single unique value with many occurrences
	{
		vector<int> v(100, 42);
		compress(v);
		for (int x : v) {
			assert(x == 0);
		}
	}

	// Test 17: Every element is unique
	{
		vector<int> v = {10, 30, 20, 50, 40};
		compress(v);
		// Ranks: 10->0, 20->1, 30->2, 40->3, 50->4
		vector<int> expected = {0, 2, 1, 4, 3};
		assert(v == expected);
	}

	cout << "All compress_inplace tests passed!" << endl;
	return 0;
}

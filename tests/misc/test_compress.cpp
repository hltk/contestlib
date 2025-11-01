#include <vector>
#include <algorithm>
using namespace std;

#include "../../misc/compress.cpp"
#include <cassert>
#include <iostream>

int main() {
	// Test 1: Simple sequence
	{
		vector<int> v = {5, 2, 8, 2, 1};
		auto result = compress(v);
		// Sorted: [1, 2, 2, 5, 8]
		// Original positions: 5->3, 2->1, 8->4, 2->1, 1->0
		vector<int> expected = {3, 1, 4, 1, 0};
		assert(result == expected);
	}

	// Test 2: Already sorted
	{
		vector<int> v = {1, 2, 3, 4, 5};
		auto result = compress(v);
		vector<int> expected = {0, 1, 2, 3, 4};
		assert(result == expected);
	}

	// Test 3: Reverse sorted
	{
		vector<int> v = {5, 4, 3, 2, 1};
		auto result = compress(v);
		// Sorted: [1, 2, 3, 4, 5]
		// Original: 5->4, 4->3, 3->2, 2->1, 1->0
		vector<int> expected = {4, 3, 2, 1, 0};
		assert(result == expected);
	}

	// Test 4: All same elements
	{
		vector<int> v = {7, 7, 7, 7};
		auto result = compress(v);
		vector<int> expected = {0, 0, 0, 0};
		assert(result == expected);
	}

	// Test 5: Single element
	{
		vector<int> v = {42};
		auto result = compress(v);
		vector<int> expected = {0};
		assert(result == expected);
	}

	// Test 6: Two elements
	{
		vector<int> v = {10, 5};
		auto result = compress(v);
		// Sorted: [5, 10]
		// Original: 10->1, 5->0
		vector<int> expected = {1, 0};
		assert(result == expected);
	}

	// Test 7: With duplicates maintaining stable order
	{
		vector<int> v = {3, 1, 4, 1, 5};
		auto result = compress(v);
		// Sorted (stable): [1, 1, 3, 4, 5]
		// Original: 3->2, 1->0, 4->3, 1->0, 5->4
		vector<int> expected = {2, 0, 3, 0, 4};
		assert(result == expected);
	}

	// Test 8: Negative numbers
	{
		vector<int> v = {-5, 0, -10, 5, -2};
		auto result = compress(v);
		// Sorted: [-10, -5, -2, 0, 5]
		// Original: -5->1, 0->3, -10->0, 5->4, -2->2
		vector<int> expected = {1, 3, 0, 4, 2};
		assert(result == expected);
	}

	// Test 9: Large numbers
	{
		vector<int> v = {1000000, 1, 999999, 2};
		auto result = compress(v);
		// Sorted: [1, 2, 999999, 1000000]
		// Original: 1000000->3, 1->0, 999999->2, 2->1
		vector<int> expected = {3, 0, 2, 1};
		assert(result == expected);
	}

	// Test 10: With strings
	{
		vector<string> v = {"dog", "cat", "elephant", "cat", "ant"};
		auto result = compress(v);
		// Sorted: ["ant", "cat", "cat", "dog", "elephant"]
		// Original: "dog"->3, "cat"->1, "elephant"->4, "cat"->1, "ant"->0
		vector<int> expected = {3, 1, 4, 1, 0};
		assert(result == expected);
	}

	// Test 11: Preserves relative order of duplicates
	{
		vector<int> v = {5, 5, 3, 3, 5};
		auto result = compress(v);
		// Sorted (stable): [3, 3, 5, 5, 5]
		// Original: 5->2, 5->2, 3->0, 3->0, 5->2
		vector<int> expected = {2, 2, 0, 0, 2};
		assert(result == expected);
	}

	// Test 12: Many duplicates
	{
		vector<int> v = {1, 2, 1, 2, 1, 2};
		auto result = compress(v);
		// Sorted: [1, 1, 1, 2, 2, 2]
		// Original: 1->0, 2->3, 1->0, 2->3, 1->0, 2->3
		vector<int> expected = {0, 3, 0, 3, 0, 3};
		assert(result == expected);
	}

	// Test 13: Floating point
	{
		vector<double> v = {3.14, 2.71, 1.41, 2.71};
		auto result = compress(v);
		// Sorted: [1.41, 2.71, 2.71, 3.14]
		// Original: 3.14->3, 2.71->1, 1.41->0, 2.71->1
		vector<int> expected = {3, 1, 0, 1};
		assert(result == expected);
	}

	// Test 14: Zero-based check
	{
		vector<int> v = {100, 200, 300};
		auto result = compress(v);
		// Result should be 0-based indices
		assert(result[0] == 0);  // 100 is smallest
		assert(result[1] == 1);  // 200 is middle
		assert(result[2] == 2);  // 300 is largest
	}

	// Test 15: Larger dataset
	{
		vector<int> v = {9, 3, 7, 3, 1, 9, 5, 3};
		auto result = compress(v);
		// Sorted: [1, 3, 3, 3, 5, 7, 9, 9]
		// Original: 9->6, 3->1, 7->5, 3->1, 1->0, 9->6, 5->4, 3->1
		vector<int> expected = {6, 1, 5, 1, 0, 6, 4, 1};
		assert(result == expected);
	}

	cout << "All compress tests passed!" << endl;
	return 0;
}

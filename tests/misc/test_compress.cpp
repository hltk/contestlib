#include <vector>
#include <algorithm>
using namespace std;

#include "../../misc/compress.cpp"
#include <cassert>
#include <iostream>
#include <random>

int main() {
	// Test 1: Basic compression
	{
		vector<int> v = {5, 2, 8, 2, 5, 1};
		vector<int> compressed = compress(v);
		
		// compressed[i] is the position in sorted array
		// Sorted: [1, 2, 2, 5, 5, 8]
		assert(compressed[5] == 0);  // 1 is at position 0
		assert(compressed[1] == 1 || compressed[1] == 2);  // 2 is at position 1 or 2
		assert(compressed[3] == 1 || compressed[3] == 2);  // 2 is at position 1 or 2
		assert(compressed[0] == 3 || compressed[0] == 4);  // 5 is at position 3 or 4
		assert(compressed[4] == 3 || compressed[4] == 4);  // 5 is at position 3 or 4
		assert(compressed[2] == 5);  // 8 is at position 5
	}

	// Test 2: Already sorted
	{
		vector<int> v = {1, 2, 3, 4, 5};
		vector<int> compressed = compress(v);
		assert(compressed == vector<int>({0, 1, 2, 3, 4}));
	}

	// Test 3: Reverse sorted
	{
		vector<int> v = {5, 4, 3, 2, 1};
		vector<int> compressed = compress(v);
		assert(compressed == vector<int>({4, 3, 2, 1, 0}));
	}

	// Test 4: All same
	{
		vector<int> v = {7, 7, 7, 7};
		vector<int> compressed = compress(v);
		assert(compressed == vector<int>({0, 0, 0, 0}));
	}

	// Test 5: Single element
	{
		vector<int> v = {42};
		vector<int> compressed = compress(v);
		assert(compressed == vector<int>({0}));
	}

	// Test 6: Two elements same
	{
		vector<int> v = {3, 3};
		vector<int> compressed = compress(v);
		assert(compressed == vector<int>({0, 0}));
	}

	// Test 7: Two elements different
	{
		vector<int> v = {3, 1};
		vector<int> compressed = compress(v);
		assert(compressed[0] > compressed[1]);  // 3 > 1
	}

	// Test 8: Negative numbers
	{
		vector<int> v = {-5, 0, 10, -5, 0};
		vector<int> compressed = compress(v);
		assert(compressed[0] == compressed[3]);  // Both -5
		assert(compressed[1] == compressed[4]);  // Both 0
		assert(compressed[0] < compressed[1]);   // -5 < 0
		assert(compressed[1] < compressed[2]);   // 0 < 10
	}

	// Test 9: Preserves relative order
	{
		vector<int> v = {10, 20, 15, 20, 10};
		vector<int> compressed = compress(v);
		
		// Equal elements should have same compressed value
		assert(compressed[0] == compressed[4]);
		assert(compressed[1] == compressed[3]);
		
		// Order should be preserved
		assert(compressed[0] < compressed[2]);  // 10 < 15
		assert(compressed[2] < compressed[1]);  // 15 < 20
	}

	// Test 10: Large range compressed to small
	{
		vector<int> v = {1000000, 1, 999999, 1000000};
		vector<int> compressed = compress(v);
		
		assert(compressed[0] == compressed[3]);  // Both 1000000
		assert(compressed[1] == 0);              // Smallest
		assert(compressed[2] == 1);              // Middle
		assert(compressed[0] == 2);              // Largest
	}

	// Test 11: Fuzzy testing
	{
		mt19937 rng(42);
		
		for (int test = 0; test < 100; test++) {
			int n = 1 + rng() % 50;
			vector<int> v(n);
			
			for (int& x : v) {
				x = (rng() % 20) - 10;  // -10 to 9
			}
			
			vector<int> compressed = compress(v);
			
			// Verify size
			assert(int(compressed.size()) == n);
			
			// Verify relative order
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (v[i] < v[j]) {
						assert(compressed[i] < compressed[j]);
					} else if (v[i] == v[j]) {
						assert(compressed[i] == compressed[j]);
					} else {
						assert(compressed[i] > compressed[j]);
					}
				}
			}
		}
	}

	// Test 12: Strings
	{
		vector<string> v = {"zebra", "apple", "banana", "apple"};
		vector<int> compressed = compress(v);
		
		assert(compressed[1] == compressed[3]);  // Both "apple"
		assert(compressed[1] < compressed[2]);   // "apple" < "banana"
		assert(compressed[2] < compressed[0]);   // "banana" < "zebra"
	}

	cout << "All Compress tests passed!" << endl;
	return 0;
}


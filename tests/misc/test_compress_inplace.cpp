#include "../../misc/compress_inplace.cpp"
#include <cassert>
#include <iostream>
#include <random>

using namespace std;

int main() {
	// Test 1: Basic compression
	{
		vector<int> v = {5, 2, 8, 2, 5, 1};
		compress(v);
		
		// After compression, values should be 0-indexed ranks
		// Original: {5, 2, 8, 2, 5, 1}
		// Unique sorted: {1, 2, 5, 8}
		// Compressed: {2, 1, 3, 1, 2, 0}
		assert(v[5] == 0);  // 1 -> 0
		assert(v[1] == 1 && v[3] == 1);  // Both 2 -> 1
		assert(v[0] == 2 && v[4] == 2);  // Both 5 -> 2
		assert(v[2] == 3);  // 8 -> 3
	}

	// Test 2: Already compressed
	{
		vector<int> v = {0, 1, 2, 3};
		compress(v);
		assert(v == vector<int>({0, 1, 2, 3}));
	}

	// Test 3: All same
	{
		vector<int> v = {7, 7, 7, 7};
		compress(v);
		assert(v == vector<int>({0, 0, 0, 0}));
	}

	// Test 4: Single element
	{
		vector<int> v = {42};
		compress(v);
		assert(v == vector<int>({0}));
	}

	// Test 5: Two elements
	{
		vector<int> v = {5, 3};
		compress(v);
		assert(v[1] == 0);  // 3 is smaller
		assert(v[0] == 1);  // 5 is larger
	}

	// Test 6: Reverse sorted
	{
		vector<int> v = {5, 4, 3, 2, 1};
		compress(v);
		assert(v == vector<int>({4, 3, 2, 1, 0}));
	}

	// Test 7: Negative numbers
	{
		vector<int> v = {-5, 0, 10, -5, 0};
		compress(v);
		assert(v[0] == 0 && v[3] == 0);  // Both -5
		assert(v[1] == 1 && v[4] == 1);  // Both 0
		assert(v[2] == 2);  // 10
	}

	// Test 8: Large range to small
	{
		vector<int> v = {1000000, 1, 999999, 1000000};
		compress(v);
		assert(v[1] == 0);  // 1 is smallest
		assert(v[2] == 1);  // 999999 is middle
		assert(v[0] == 2 && v[3] == 2);  // Both 1000000
	}

	// Test 9: Duplicates
	{
		vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5};
		compress(v);
		
		// Check duplicates have same value
		assert(v[1] == v[3]);  // Both 1
		assert(v[4] == v[8]);  // Both 5
	}

	// Test 10: Fuzzy testing
	{
		mt19937 rng(42);
		
		for (int test = 0; test < 100; test++) {
			int n = 1 + rng() % 50;
			vector<int> orig(n);
			
			for (int& x : orig) {
				x = (rng() % 20) - 10;
			}
			
			vector<int> v = orig;
			compress(v);
			
			// Verify all values are in [0, n)
			for (int x : v) {
				assert(x >= 0 && x < n);
			}
			
			// Verify relative order
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (orig[i] < orig[j]) {
						assert(v[i] < v[j]);
					} else if (orig[i] == orig[j]) {
						assert(v[i] == v[j]);
					} else {
						assert(v[i] > v[j]);
					}
				}
			}
		}
	}

	// Test 11: Works only with numeric types since it assigns int values

	// Test 12: Check it's 0-indexed
	{
		vector<int> v = {100, 200, 300};
		compress(v);
		assert(v[0] == 0);
		assert(v[1] == 1);
		assert(v[2] == 2);
	}

	cout << "All Compress In-Place tests passed!" << endl;
	return 0;
}


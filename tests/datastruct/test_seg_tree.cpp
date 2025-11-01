#include "../../datastruct/seg_tree.cpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <climits>

using namespace std;

// Naive range query for verification
int naive_min(const vector<int>& arr, int a, int b) {
	int minval = arr[a];
	for (int i = a + 1; i < b; i++) {
		minval = min(minval, arr[i]);
	}
	return minval;
}

int naive_sum(const vector<int>& arr, int a, int b) {
	int sum = 0;
	for (int i = a; i < b; i++) {
		sum += arr[i];
	}
	return sum;
}

int main() {
	// Test 1: Basic min tree
	{
		Tree<int> tree(8, INT_MAX, [](int a, int b) { return min(a, b); });
		
		tree.change(0, 5);
		tree.change(1, 3);
		tree.change(2, 7);
		tree.change(3, 1);
		tree.change(4, 9);
		
		assert(tree.query(0, 5) == 1);
		assert(tree.query(0, 2) == 3);
		assert(tree.query(2, 5) == 1);
	}

	// Test 2: Sum tree
	{
		Tree<int> tree(8, 0, [](int a, int b) { return a + b; });
		
		for (int i = 0; i < 5; i++) {
			tree.change(i, i + 1);  // 1, 2, 3, 4, 5
		}
		
		assert(tree.query(0, 5) == 15);
		assert(tree.query(0, 3) == 6);
		assert(tree.query(2, 5) == 12);
	}

	// Test 3: Single element queries
	{
		Tree<int> tree(4, INT_MAX, [](int a, int b) { return min(a, b); });
		
		tree.change(0, 10);
		tree.change(1, 20);
		tree.change(2, 30);
		
		assert(tree.query(0, 1) == 10);
		assert(tree.query(1, 2) == 20);
		assert(tree.query(2, 3) == 30);
	}

	// Test 4: Update and query
	{
		Tree<int> tree(8, 0, [](int a, int b) { return a + b; });
		
		tree.change(2, 10);
		assert(tree.query(0, 8) == 10);
		
		tree.change(2, 5);  // Replace, not add
		assert(tree.query(0, 8) == 5);
		
		tree.change(4, 3);
		assert(tree.query(0, 8) == 8);
	}

	// Test 5: Max tree
	{
		Tree<int> tree(8, INT_MIN, [](int a, int b) { return max(a, b); });
		
		tree.change(0, 5);
		tree.change(1, 9);
		tree.change(2, 3);
		tree.change(3, 7);
		
		assert(tree.query(0, 4) == 9);
		assert(tree.query(0, 1) == 5);
		assert(tree.query(2, 4) == 7);
	}

	// Test 6: GCD tree
	{
		auto gcd = [](int a, int b) {
			while (b) {
				int t = b;
				b = a % b;
				a = t;
			}
			return a;
		};
		
		Tree<int> tree(8, 0, gcd);
		
		tree.change(0, 12);
		tree.change(1, 18);
		tree.change(2, 24);
		
		assert(tree.query(0, 3) == 6);
		assert(tree.query(0, 2) == 6);
		assert(tree.query(1, 3) == 6);
	}

	// Test 7: Empty range behavior with identity
	{
		Tree<int> tree(4, 0, [](int a, int b) { return a + b; });
		tree.change(0, 5);
		tree.change(1, 10);
		
		// Empty range should return identity
		assert(tree.query(2, 2) == 0);
	}

	// Test 8: Power of 2 sizes
	{
		for (int n : {1, 2, 4, 8, 16, 32, 64, 128}) {
			Tree<int> tree(n, 0, [](int a, int b) { return a + b; });
			
			for (int i = 0; i < n; i++) {
				tree.change(i, 1);
			}
			
			assert(tree.query(0, n) == n);
		}
	}

	// Test 9: Fuzzy testing with min tree
	{
		mt19937 rng(42);
		
		for (int test = 0; test < 100; test++) {
			int n = 1 << (1 + rng() % 6);  // Power of 2: 2, 4, 8, 16, 32, 64
			vector<int> arr(n, INT_MAX);
			Tree<int> tree(n, INT_MAX, [](int a, int b) { return min(a, b); });
			
			// Random updates
			for (int op = 0; op < 30; op++) {
				int pos = rng() % n;
				int val = rng() % 100;
				
				arr[pos] = val;
				tree.change(pos, val);
			}
			
			// Test random queries
			for (int q = 0; q < 20; q++) {
				int a = rng() % n;
				int b = a + 1 + rng() % (n - a);
				
				assert(tree.query(a, b) == naive_min(arr, a, b));
			}
		}
	}

	// Test 10: Fuzzy testing with sum tree
	{
		mt19937 rng(42);
		
		for (int test = 0; test < 100; test++) {
			int n = 1 << (1 + rng() % 6);  // Power of 2
			vector<int> arr(n, 0);
			Tree<int> tree(n, 0, [](int a, int b) { return a + b; });
			
			// Random updates
			for (int op = 0; op < 30; op++) {
				int pos = rng() % n;
				int val = (rng() % 50) - 25;  // -25 to 24
				
				arr[pos] = val;
				tree.change(pos, val);
			}
			
			// Test random queries
			for (int q = 0; q < 20; q++) {
				int a = rng() % n;
				int b = a + 1 + rng() % (n - a);
				
				assert(tree.query(a, b) == naive_sum(arr, a, b));
			}
		}
	}

	// Test 11: Adjacent ranges
	{
		Tree<int> tree(8, 0, [](int a, int b) { return a + b; });
		
		for (int i = 0; i < 5; i++) {
			tree.change(i, i + 1);
		}
		
		// Query adjacent ranges and verify they sum correctly
		int sum1 = tree.query(0, 2);
		int sum2 = tree.query(2, 5);
		assert(sum1 + sum2 == tree.query(0, 5));
	}

	cout << "All Segment Tree tests passed!" << endl;
	return 0;
}


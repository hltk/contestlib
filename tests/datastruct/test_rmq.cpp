#include "../../datastruct/rmq.cpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

// Naive RMQ for verification
template<typename T>
T naive_min(const vector<T>& arr, int l, int r) {
	T minval = arr[l];
	for (int i = l + 1; i <= r; i++) {
		minval = min(minval, arr[i]);
	}
	return minval;
}

int main() {
	// Test 1: Basic min query
	{
		vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
		RMQ<int> rmq(v);
		
		assert(rmq.getmin(0, 7) == 1);
		assert(rmq.getmin(0, 0) == 3);
		assert(rmq.getmin(2, 5) == 1);
		assert(rmq.getmin(5, 7) == 2);
	}

	// Test 2: Single element
	{
		vector<int> v = {42};
		RMQ<int> rmq(v);
		assert(rmq.getmin(0, 0) == 42);
		assert(rmq.argmin(0, 0) == 0);
	}

	// Test 3: All same elements
	{
		vector<int> v(10, 5);
		RMQ<int> rmq(v);
		assert(rmq.getmin(0, 9) == 5);
		assert(rmq.getmin(3, 7) == 5);
		// Just verify argmin returns valid index 
		int idx = rmq.argmin(0, 9);
		assert(idx >= 0 && idx <= 9);
		assert(v[idx] == 5);
	}

	// Test 4: Sorted array
	{
		vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
		RMQ<int> rmq(v);
		
		for (int l = 0; l < 8; l++) {
			for (int r = l; r < 8; r++) {
				assert(rmq.getmin(l, r) == v[l]);
				assert(rmq.argmin(l, r) == l);
			}
		}
	}

	// Test 5: Reverse sorted array
	{
		vector<int> v = {8, 7, 6, 5, 4, 3, 2, 1};
		RMQ<int> rmq(v);
		
		for (int l = 0; l < 8; l++) {
			for (int r = l; r < 8; r++) {
				assert(rmq.getmin(l, r) == v[r]);
				assert(rmq.argmin(l, r) == r);
			}
		}
	}

	// Test 6: Negative values
	{
		vector<int> v = {-5, 3, -2, 8, -10, 4};
		RMQ<int> rmq(v);
		
		assert(rmq.getmin(0, 5) == -10);
		assert(rmq.getmin(0, 2) == -5);
		assert(rmq.getmin(1, 3) == -2);
		assert(rmq.argmin(0, 5) == 4);
	}

	// Test 7: RMQ with max (using greater<int>)
	{
		vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
		RMQ<int, greater<int>> rmq(v);
		
		assert(rmq.getmin(0, 7) == 9);  // Actually max
		assert(rmq.getmin(0, 2) == 4);
		assert(rmq.getmin(3, 7) == 9);
	}

	// Test 8: Power of 2 sizes
	{
		for (int n : {1, 2, 4, 8, 16, 32, 64}) {
			vector<int> v(n);
			for (int i = 0; i < n; i++) {
				v[i] = n - i;  // Decreasing
			}
			RMQ<int> rmq(v);
			assert(rmq.getmin(0, n - 1) == 1);
			assert(rmq.argmin(0, n - 1) == n - 1);
		}
	}

	// Test 9: Fuzzy testing
	{
		mt19937 rng(42);
		
		for (int test = 0; test < 100; test++) {
			int n = 1 + rng() % 50;
			vector<int> v(n);
			
			for (int& x : v) {
				x = (rng() % 200) - 100;  // -100 to 99
			}
			
			RMQ<int> rmq(v);
			
			// Test random queries
			for (int q = 0; q < 20; q++) {
				int l = rng() % n;
				int r = l + rng() % (n - l);
				
				assert(rmq.getmin(l, r) == naive_min(v, l, r));
				int argmin_idx = rmq.argmin(l, r);
				assert(v[argmin_idx] == naive_min(v, l, r));
				assert(argmin_idx >= l && argmin_idx <= r);
			}
		}
	}

	// Test 10: Argmin returns valid index on ties
	{
		vector<int> v = {3, 1, 1, 1, 5};
		RMQ<int> rmq(v);
		
		int idx1 = rmq.argmin(0, 4);
		assert(idx1 >= 0 && idx1 <= 4);
		assert(v[idx1] == 1);  // Should be one of the minimums
		
		int idx2 = rmq.argmin(1, 3);
		assert(idx2 >= 1 && idx2 <= 3);
		assert(v[idx2] == 1);
	}

	// Test 11: Adjacent elements
	{
		vector<int> v = {5, 3, 8, 2, 9};
		RMQ<int> rmq(v);
		
		for (int i = 0; i < 4; i++) {
			int expected = min(v[i], v[i + 1]);
			assert(rmq.getmin(i, i + 1) == expected);
		}
	}

	cout << "All RMQ tests passed!" << endl;
	return 0;
}


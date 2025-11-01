#include "../../datastruct/short_rmq.cpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <random>

using namespace std;

// Naive RMQ for verification
int naive_min(const vector<int>& arr, int a, int b) {
	int minval = arr[a];
	for (int i = a + 1; i < b; i++) {
		minval = min(minval, arr[i]);
	}
	return minval;
}

int main() {
	// Test 1: Basic min queries
	{
		vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
		RMQ<int> rmq(v);
		
		assert(rmq.getmin(0, 7) == 1);
		assert(rmq.getmin(0, 2) == 1);
		assert(rmq.getmin(4, 7) == 2);
		assert(rmq.getmin(5, 6) == 2);
	}

	// Test 2: Single element queries
	{
		vector<int> v = {10, 20, 30, 40, 50};
		RMQ<int> rmq(v);
		
		assert(rmq.getmin(0, 0) == 10);
		assert(rmq.getmin(1, 1) == 20);
		assert(rmq.getmin(4, 4) == 50);
	}

	// Test 3: Entire array query
	{
		vector<int> v = {5, 2, 8, 1, 9, 3, 7};
		RMQ<int> rmq(v);
		
		assert(rmq.getmin(0, v.size() - 1) == 1);
	}

	// Test 4: Array with duplicates
	{
		vector<int> v = {5, 3, 3, 5, 3, 3, 5};
		RMQ<int> rmq(v);
		
		// Should return minimum (any of the 3s)
		assert(rmq.getmin(0, v.size() - 1) == 3);
		assert(rmq.getmin(0, 1) == 3);
		assert(rmq.getmin(3, 6) == 3);
	}

	// Test 5: Increasing array
	{
		vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
		RMQ<int> rmq(v);
		
		// Minimum should always be at the left end of range
		assert(rmq.getmin(0, 7) == 1);
		assert(rmq.getmin(2, 5) == 3);
		assert(rmq.getmin(4, 7) == 5);
	}

	// Test 6: Decreasing array
	{
		vector<int> v = {8, 7, 6, 5, 4, 3, 2, 1};
		RMQ<int> rmq(v);
		
		// Minimum should always be at the right end of range
		assert(rmq.getmin(0, 7) == 1);
		assert(rmq.getmin(2, 5) == 3);
		assert(rmq.getmin(4, 7) == 1);
	}

	// Test 7: Random array with comprehensive testing
	{
		mt19937 rng(42);
		vector<int> v(100);
		for (int& x : v) {
			x = rng() % 1000;
		}
		
		RMQ<int> rmq(v);
		
		// Test many random queries
		for (int test = 0; test < 200; test++) {
			int l = rng() % v.size();
			int r = l + rng() % (v.size() - l);
			
			int result = rmq.getmin(l, r);
			int expected = naive_min(v, l, r + 1);  // getmin uses inclusive end
			
			assert(result == expected);
		}
	}

	// Test 8: Valley pattern
	{
		vector<int> v = {10, 8, 6, 4, 2, 4, 6, 8, 10};
		RMQ<int> rmq(v);
		
		// Minimum is in the middle
		assert(rmq.getmin(0, 8) == 2);
		assert(rmq.getmin(0, 4) == 2);
		assert(rmq.getmin(4, 8) == 2);
		assert(rmq.getmin(0, 3) == 4);
		assert(rmq.getmin(5, 8) == 4);
	}

	// Test 9: Mountain pattern
	{
		vector<int> v = {1, 3, 5, 7, 9, 7, 5, 3, 1};
		RMQ<int> rmq(v);
		
		// Minimum should be at the ends
		assert(rmq.getmin(0, 8) == 1);
		assert(rmq.getmin(1, 7) == 3);
		assert(rmq.getmin(2, 6) == 5);
	}

	// Test 10: All same values
	{
		vector<int> v(50, 42);
		RMQ<int> rmq(v);
		
		// Any query should return 42
		assert(rmq.getmin(0, 49) == 42);
		assert(rmq.getmin(10, 20) == 42);
		assert(rmq.getmin(25, 25) == 42);
	}

	// Test 11: Two element array
	{
		vector<int> v = {5, 3};
		RMQ<int> rmq(v);
		
		assert(rmq.getmin(0, 1) == 3);
		assert(rmq.getmin(0, 0) == 5);
		assert(rmq.getmin(1, 1) == 3);
	}

	// Test 12: Large array stress test
	{
		mt19937 rng(12345);
		vector<int> v(1000);
		for (int& x : v) {
			x = rng() % 10000;
		}
		
		RMQ<int> rmq(v);
		
		// Test 100 random queries
		for (int test = 0; test < 100; test++) {
			int l = rng() % v.size();
			int r = l + rng() % (v.size() - l);
			
			int result = rmq.getmin(l, r);
			int expected = naive_min(v, l, r + 1);
			
			assert(result == expected);
		}
	}

	// Test 13: Negative values
	{
		vector<int> v = {-5, -10, -3, -15, -8, -1, -20};
		RMQ<int> rmq(v);
		
		assert(rmq.getmin(0, 6) == -20);
		assert(rmq.getmin(0, 2) == -10);
		assert(rmq.getmin(4, 6) == -20);
	}

	// Test 14: Max RMQ using custom comparator
	{
		vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
		RMQ<int, greater<int>> rmq(v);  // Max instead of min
		
		assert(rmq.getmin(0, 7) == 9);
		assert(rmq.getmin(0, 2) == 4);
		assert(rmq.getmin(4, 7) == 9);
	}

	cout << "All Short RMQ tests passed!" << endl;
	return 0;
}


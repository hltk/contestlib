#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

// Include only the structs, not the main function
#define main main_disabled
#include "../../datastruct/linear_rmq.cpp"
#undef main

// Naive RMQ for verification
int naive_rmq(const vector<int>& v, int l, int r) {
	int minval = v[l];
	for (int i = l + 1; i <= r; i++) {
		minval = min(minval, v[i]);
	}
	return minval;
}

int main() {
	// Test 1: Basic RMQ queries
	{
		vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
		RMQ rmq(v);
		
		assert(v[rmq.query(0, 7)] == 1);
		assert(v[rmq.query(0, 2)] == 1);
		assert(v[rmq.query(4, 7)] == 2);
		assert(v[rmq.query(5, 6)] == 2);
	}

	// Test 2: Single element queries
	{
		vector<int> v = {10, 20, 30, 40, 50};
		RMQ rmq(v);
		
		assert(v[rmq.query(0, 0)] == 10);
		assert(v[rmq.query(1, 1)] == 20);
		assert(v[rmq.query(4, 4)] == 50);
	}

	// Test 3: Entire array query
	{
		vector<int> v = {5, 2, 8, 1, 9, 3, 7};
		RMQ rmq(v);
		
		int idx = rmq.query(0, v.size() - 1);
		assert(v[idx] == 1);
	}

	// Test 4: Array with duplicates
	{
		vector<int> v = {5, 3, 3, 5, 3, 3, 5};
		RMQ rmq(v);
		
		// Should return index of minimum (any of the 3s)
		int idx = rmq.query(0, v.size() - 1);
		assert(v[idx] == 3);
		
		// Query specific ranges
		assert(v[rmq.query(0, 1)] == 3);
		assert(v[rmq.query(3, 6)] == 3);
	}

	// Test 5: Increasing array
	{
		vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
		RMQ rmq(v);
		
		// Minimum should always be at the left end
		assert(v[rmq.query(0, 7)] == 1);
		assert(v[rmq.query(2, 5)] == 3);
		assert(v[rmq.query(4, 7)] == 5);
	}

	// Test 6: Decreasing array
	{
		vector<int> v = {8, 7, 6, 5, 4, 3, 2, 1};
		RMQ rmq(v);
		
		// Minimum should always be at the right end
		assert(v[rmq.query(0, 7)] == 1);
		assert(v[rmq.query(2, 5)] == 3);
		assert(v[rmq.query(4, 7)] == 1);
	}

	// Test 7: Random array with comprehensive testing
	{
		mt19937 rng(42);
		vector<int> v(100);
		for (int& x : v) {
			x = rng() % 1000;
		}
		
		RMQ rmq(v);
		
		// Test many random queries
		for (int test = 0; test < 200; test++) {
			int l = rng() % v.size();
			int r = l + rng() % (v.size() - l);
			
			int idx = rmq.query(l, r);
			int expected_val = naive_rmq(v, l, r);
			
			assert(v[idx] == expected_val);
		}
	}

	// Test 8: Valley pattern
	{
		vector<int> v = {10, 8, 6, 4, 2, 4, 6, 8, 10};
		RMQ rmq(v);
		
		// Minimum is in the middle
		assert(v[rmq.query(0, 8)] == 2);
		assert(v[rmq.query(0, 4)] == 2);
		assert(v[rmq.query(4, 8)] == 2);
		assert(v[rmq.query(0, 3)] == 4);
		assert(v[rmq.query(5, 8)] == 4);
	}

	// Test 9: Mountain pattern
	{
		vector<int> v = {1, 3, 5, 7, 9, 7, 5, 3, 1};
		RMQ rmq(v);
		
		// Minimum should be at the ends
		assert(v[rmq.query(0, 8)] == 1);
		assert(v[rmq.query(1, 7)] == 3);
		assert(v[rmq.query(2, 6)] == 5);
	}

	// Test 10: All same values
	{
		vector<int> v(50, 42);
		RMQ rmq(v);
		
		// Any index should work, value should be 42
		assert(v[rmq.query(0, 49)] == 42);
		assert(v[rmq.query(10, 20)] == 42);
		assert(v[rmq.query(25, 25)] == 42);
	}

	// Test 11: Two element array
	{
		vector<int> v = {5, 3};
		RMQ rmq(v);
		
		assert(v[rmq.query(0, 1)] == 3);
		assert(v[rmq.query(0, 0)] == 5);
		assert(v[rmq.query(1, 1)] == 3);
	}

	// Test 12: Large array stress test
	{
		mt19937 rng(12345);
		vector<int> v(1000);
		for (int& x : v) {
			x = rng() % 10000;
		}
		
		RMQ rmq(v);
		
		// Test 100 random queries
		for (int test = 0; test < 100; test++) {
			int l = rng() % v.size();
			int r = l + rng() % (v.size() - l);
			
			int idx = rmq.query(l, r);
			int expected_val = naive_rmq(v, l, r);
			
			assert(v[idx] == expected_val);
		}
	}

	// Test 13: Negative values
	{
		vector<int> v = {-5, -10, -3, -15, -8, -1, -20};
		RMQ rmq(v);
		
		assert(v[rmq.query(0, 6)] == -20);
		assert(v[rmq.query(0, 2)] == -10);
		assert(v[rmq.query(4, 6)] == -20);
	}

	cout << "All Linear RMQ tests passed!" << endl;
	return 0;
}


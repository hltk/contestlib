#include "../../misc/bins.cpp"
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

int main() {
	// Test 1: Basic binary search
	{
		auto f = [](int x) { return x >= 5; };
		int result = bins(0, 10, f);
		assert(result == 5);
	}

	// Test 2: All false
	{
		auto f = [](int x) { return x >= 100; };
		int result = bins(0, 10, f);
		assert(result == 10);  // Returns r
	}

	// Test 3: All true
	{
		auto f = [](int x) { return x >= 0; };
		int result = bins(0, 10, f);
		assert(result == 0);
	}

	// Test 4: First true at beginning
	{
		auto f = [](int x) { return x >= 1; };
		int result = bins(1, 10, f);
		assert(result == 1);
	}

	// Test 5: First true at end
	{
		auto f = [](int x) { return x >= 9; };
		int result = bins(0, 10, f);
		assert(result == 9);
	}

	// Test 6: Range of size 1
	{
		auto f = [](int x) { return x >= 5; };
		int result = bins(5, 6, f);
		assert(result == 5);
	}

	// Test 7: With doubles
	{
		auto f = [](double x) { return x >= 3.5; };
		double result = bins(0.0, 10.0, f);
		assert(result >= 3.5 - 1e-9 && result <= 3.5 + 1e-9);
	}

	// Test 8: Negative ranges
	{
		auto f = [](int x) { return x >= -5; };
		int result = bins(-10, 0, f);
		assert(result == -5);
	}

	// Test 9: Sqrt using binary search
	{
		auto f = [](double x) { return x * x >= 2.0; };
		double result = bins(0.0, 2.0, f);
		// sqrt(2) ≈ 1.414
		assert(result * result >= 2.0 - 1e-6);
	}

	// Test 10: Large range
	{
		auto f = [](long long x) { return x >= 500000; };
		long long result = bins(0LL, 1000000LL, f);
		assert(result == 500000);
	}

	// Test 11: Monotonic function
	{
		// x^2 >= 16, so x >= 4
		auto f = [](int x) { return x * x >= 16; };
		int result = bins(0, 10, f);
		assert(result == 4);
	}

	// Test 12: Complex predicate
	{
		vector<int> arr = {1, 3, 5, 7, 9, 11, 13};
		auto f = [&](int idx) { return arr[idx] >= 7; };
		int result = bins(0, (int)arr.size(), f);
		assert(result == 3);  // Index of first element >= 7
		assert(arr[result] == 7);
	}

	cout << "All Bins tests passed!" << endl;
	return 0;
}


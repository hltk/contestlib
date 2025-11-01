#include "../../misc/bins.cpp"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	// Test 1: Find exact value in sorted array
	{
		vector<int> arr = {1, 3, 5, 7, 9, 11, 13};
		auto f = [&](int i) { return arr[i] >= 7; };
		int result = bins(0, (int)arr.size(), f);
		assert(result == 3);  // arr[3] = 7
	}

	// Test 2: Find insertion point
	{
		vector<int> arr = {1, 3, 5, 9, 11, 13};
		auto f = [&](int i) { return arr[i] >= 7; };
		int result = bins(0, (int)arr.size(), f);
		assert(result == 3);  // Insert 7 at position 3
	}

	// Test 3: All elements satisfy predicate
	{
		vector<int> arr = {5, 6, 7, 8, 9};
		auto f = [&](int i) { return arr[i] >= 4; };
		int result = bins(0, (int)arr.size(), f);
		assert(result == 0);  // First element
	}

	// Test 4: No elements satisfy predicate
	{
		vector<int> arr = {1, 2, 3, 4, 5};
		auto f = [&](int i) { return arr[i] >= 10; };
		int result = bins(0, (int)arr.size(), f);
		assert(result == 5);  // Beyond end
	}

	// Test 5: Single element - satisfies
	{
		auto f = [](int i) { return i >= 5; };
		int result = bins(5, 6, f);
		assert(result == 5);
	}

	// Test 6: Single element - doesn't satisfy
	{
		auto f = [](int i) { return i >= 10; };
		int result = bins(5, 6, f);
		assert(result == 6);
	}

	// Test 7: Empty range
	{
		auto f = [](int i) { return i >= 5; };
		int result = bins(5, 5, f);
		assert(result == 5);
	}

	// Test 8: Find square root (integer)
	{
		int target = 100;
		auto f = [target](int x) { return x * x >= target; };
		int result = bins(0, 100, f);
		assert(result == 10);  // sqrt(100) = 10
	}

	// Test 9: Find square root (non-perfect square)
	{
		int target = 50;
		auto f = [target](int x) { return x * x >= target; };
		int result = bins(0, 100, f);
		assert(result == 8);  // ceil(sqrt(50)) = 8, since 7*7=49 < 50, 8*8=64 >= 50
	}

	// Test 10: Large range
	{
		auto f = [](int x) { return x >= 500000; };
		int result = bins(0, 1000000, f);
		assert(result == 500000);
	}

	// Test 11: Find first negative in mixed array
	{
		vector<int> arr = {-10, -5, -2, 0, 3, 5, 8};
		auto f = [&](int i) { return arr[i] >= 0; };
		int result = bins(0, (int)arr.size(), f);
		assert(result == 3);  // arr[3] = 0
	}

	// Test 12: With floating point comparison
	{
		vector<double> arr = {1.1, 2.2, 3.3, 4.4, 5.5};
		auto f = [&](int i) { return arr[i] >= 3.5; };
		int result = bins(0, (int)arr.size(), f);
		assert(result == 3);  // arr[3] = 4.4
	}

	// Test 13: Find boundary (true/false transition)
	{
		// Function: i >= 42
		auto f = [](int i) { return i >= 42; };
		int result = bins(0, 100, f);
		assert(result == 42);
	}

	// Test 14: With long long
	{
		auto f = [](long long x) { return x * x >= 1000000000000LL; };
		long long result = bins(0LL, 10000000LL, f);
		assert(result == 1000000);  // ceil(sqrt(10^12))
	}

	// Test 15: Powers of 2
	{
		auto f = [](int x) { return (1 << x) >= 1024; };
		int result = bins(0, 20, f);
		assert(result == 10);  // 2^10 = 1024
	}

	cout << "All binary search tests passed!" << endl;
	return 0;
}

#include <random>
#include <chrono>
using namespace std;

#include "../../misc/rand.cpp"
#include <cassert>
#include <iostream>
#include <set>

int main() {
	// Test 1: Range check [0, 10]
	{
		for (int i = 0; i < 100; ++i) {
			int x = rand(0, 10);
			assert(x >= 0 && x <= 10);
		}
	}

	// Test 2: Range check [5, 5] (single value)
	{
		for (int i = 0; i < 10; ++i) {
			int x = rand(5, 5);
			assert(x == 5);
		}
	}

	// Test 3: Range check negative numbers
	{
		for (int i = 0; i < 100; ++i) {
			int x = rand(-10, -5);
			assert(x >= -10 && x <= -5);
		}
	}

	// Test 4: Range check large numbers
	{
		for (int i = 0; i < 100; ++i) {
			int x = rand(1000000, 1000100);
			assert(x >= 1000000 && x <= 1000100);
		}
	}

	// Test 5: Check that we get different values (not always the same)
	{
		set<int> values;
		for (int i = 0; i < 100; ++i) {
			values.insert(rand(0, 100));
		}
		// With 100 samples from [0, 100], we should get multiple distinct values
		assert(values.size() > 10);
	}

	// Test 6: Range check [0, 1] (binary)
	{
		set<int> values;
		for (int i = 0; i < 50; ++i) {
			int x = rand(0, 1);
			assert(x == 0 || x == 1);
			values.insert(x);
		}
		// Should get both 0 and 1 with high probability
		assert(values.size() == 2);
	}

	// Test 7: Long long range
	{
		for (int i = 0; i < 100; ++i) {
			long long x = rand<long long>(1000000000LL, 2000000000LL);
			assert(x >= 1000000000LL && x <= 2000000000LL);
		}
	}

	// Test 8: Check distribution coverage
	{
		// Generate numbers in [0, 9] and verify all are hit eventually
		set<int> values;
		for (int i = 0; i < 1000; ++i) {
			values.insert(rand(0, 9));
		}
		// With 1000 samples from [0, 9], we should get all 10 values
		assert(values.size() == 10);
	}

	// Test 9: Parameterless rand() returns valid int
	{
		// Can't easily test the range, but make sure it compiles and runs
		for (int i = 0; i < 10; ++i) {
			int x = rand<int>();
			(void)x;  // Use the value
		}
	}

	// Test 10: Check unsigned types
	{
		for (int i = 0; i < 100; ++i) {
			unsigned int x = rand<unsigned int>(0u, 100u);
			assert(x <= 100u);
		}
	}

	// Test 11: Verify randomness (not all values the same)
	{
		int first = rand(0, 1000000);
		bool found_different = false;
		for (int i = 0; i < 100; ++i) {
			if (rand(0, 1000000) != first) {
				found_different = true;
				break;
			}
		}
		assert(found_different);
	}

	// Test 12: Small range variability
	{
		set<int> values;
		for (int i = 0; i < 100; ++i) {
			values.insert(rand(0, 3));
		}
		// Should see at least 3 different values
		assert(values.size() >= 3);
	}

	// Test 13: Boundary values appear
	{
		bool found_0 = false, found_10 = false;
		for (int i = 0; i < 1000; ++i) {
			int x = rand(0, 10);
			if (x == 0) found_0 = true;
			if (x == 10) found_10 = true;
		}
		// Should hit boundaries with high probability
		assert(found_0 && found_10);
	}

	// Test 14: Negative to positive range
	{
		set<int> values;
		for (int i = 0; i < 100; ++i) {
			int x = rand(-5, 5);
			assert(x >= -5 && x <= 5);
			values.insert(x);
		}
		// Should get good coverage
		assert(values.size() >= 8);
	}

	// Test 15: Very large range
	{
		for (int i = 0; i < 100; ++i) {
			long long x = rand<long long>(-1000000000000LL, 1000000000000LL);
			assert(x >= -1000000000000LL && x <= 1000000000000LL);
		}
	}

	cout << "All rand tests passed!" << endl;
	return 0;
}

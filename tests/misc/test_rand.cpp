#include <chrono>
#include <random>
using namespace std;

#include "../../misc/rand.cpp"
#include <cassert>
#include <iostream>
#include <set>

int main() {
	// Test 1: rand() with range
	{
		set<int> values;
		for (int i = 0; i < 1000; i++) {
			int val = rand(1, 10);
			assert(val >= 1 && val <= 10);
			values.insert(val);
		}
		// Should have seen multiple different values
		assert(values.size() > 5);
	}

	// Test 2: rand() without arguments (full range)
	{
		// Just verify it compiles and runs
		int val = rand<int>();
		(void)val;  // Unused intentionally
	}

	// Test 3: Range of 1 (a == b)
	{
		for (int i = 0; i < 100; i++) {
			assert(rand(5, 5) == 5);
		}
	}

	// Test 4: Different ranges
	{
		for (int i = 0; i < 100; i++) {
			int val = rand(0, 0);
			assert(val == 0);
		}
		
		for (int i = 0; i < 100; i++) {
			int val = rand(100, 200);
			assert(val >= 100 && val <= 200);
		}
	}

	// Test 5: Negative ranges
	{
		for (int i = 0; i < 100; i++) {
			int val = rand(-10, -5);
			assert(val >= -10 && val <= -5);
		}
	}

	// Test 6: Large ranges
	{
		for (int i = 0; i < 100; i++) {
			long long val = rand<long long>(0LL, 1000000000LL);
			assert(val >= 0 && val <= 1000000000LL);
		}
	}

	// Test 7: Distribution check (simple)
	{
		vector<int> counts(3, 0);
		for (int i = 0; i < 3000; i++) {
			int val = rand(0, 2);
			counts[val]++;
		}
		// Each value should appear roughly 1000 times (allow 500-1500)
		for (int c : counts) {
			assert(c >= 500 && c <= 1500);
		}
	}

	// Test 8: Different types
	{
		// unsigned
		unsigned val1 = rand<unsigned>(0u, 100u);
		assert(val1 <= 100u);
		
		// long
		long val2 = rand<long>(0L, 100L);
		assert(val2 >= 0L && val2 <= 100L);
	}

	cout << "All Rand tests passed!" << endl;
	return 0;
}


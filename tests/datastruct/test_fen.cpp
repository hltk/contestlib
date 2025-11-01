#include "../../datastruct/fen.cpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

// Naive implementation for verification
template<typename T>
T naive_sum(const vector<T>& arr, int r) {
	T sum = 0;
	for (int i = 0; i < r; i++) {
		sum += arr[i];
	}
	return sum;
}

int main() {
	// Test 1: Basic operations
	{
		FenTree<int> fen(5);
		fen.update(0, 3);
		fen.update(1, 2);
		fen.update(2, 5);
		
		assert(fen.query(1) == 3);
		assert(fen.query(2) == 5);
		assert(fen.query(3) == 10);
	}

	// Test 2: Single element
	{
		FenTree<int> fen(1);
		fen.update(0, 42);
		assert(fen.query(1) == 42);
	}

	// Test 3: Multiple updates to same position
	{
		FenTree<int> fen(5);
		fen.update(2, 10);
		fen.update(2, 5);
		fen.update(2, -3);
		assert(fen.query(3) == 12);
	}

	// Test 4: Zero values
	{
		FenTree<int> fen(5);
		fen.update(0, 0);
		fen.update(2, 0);
		assert(fen.query(5) == 0);
	}

	// Test 5: Negative values
	{
		FenTree<int> fen(5);
		fen.update(0, 10);
		fen.update(1, -5);
		fen.update(2, 3);
		assert(fen.query(3) == 8);
	}

	// Test 6: Lower bound function
	{
		FenTree<int> fen(10);
		fen.update(0, 5);
		fen.update(1, 3);
		fen.update(2, 7);
		fen.update(3, 2);
		
		assert(fen.lower_bound(0) == -1);    // Empty sum
		assert(fen.lower_bound(5) == 0);     // Exactly at first element
		assert(fen.lower_bound(6) == 1);     // Need second element
		assert(fen.lower_bound(15) == 2);    // Need third element
		assert(fen.lower_bound(100) == 10);  // Sum too large, return n
	}

	// Test 7: Fuzzy testing with random operations
	{
		mt19937 rng(42);
		
		for (int test = 0; test < 100; test++) {
			int n = 1 + rng() % 50;
			vector<int> arr(n, 0);
			FenTree<int> fen(n);
			
			// Random updates
			for (int op = 0; op < 20; op++) {
				int pos = rng() % n;
				int delta = (rng() % 20) - 10;  // -10 to 9
				
				arr[pos] += delta;
				fen.update(pos, delta);
			}
			
			// Verify all prefix sums
			for (int r = 0; r <= n; r++) {
				assert(fen.query(r) == naive_sum(arr, r));
			}
		}
	}

	// Test 8: Large values
	{
		FenTree<long long> fen(10);
		fen.update(0, 1000000000LL);
		fen.update(1, 1000000000LL);
		assert(fen.query(2) == 2000000000LL);
	}

	// Test 9: Power of 2 sizes
	{
		for (int n : {1, 2, 4, 8, 16, 32, 64}) {
			FenTree<int> fen(n);
			for (int i = 0; i < n; i++) {
				fen.update(i, i + 1);
			}
			int expected = n * (n + 1) / 2;
			assert(fen.query(n) == expected);
		}
	}

	// Test 10: Lower bound edge cases
	{
		FenTree<int> fen(5);
		for (int i = 0; i < 5; i++) {
			fen.update(i, 2);  // Each position has value 2
		}
		
		assert(fen.lower_bound(1) == 0);   // First element
		assert(fen.lower_bound(2) == 0);   // Exactly first element
		assert(fen.lower_bound(3) == 1);   // Need second element
		assert(fen.lower_bound(10) == 4);  // Need all elements
		assert(fen.lower_bound(11) == 5);  // More than total sum
	}

	cout << "All Fenwick Tree tests passed!" << endl;
	return 0;
}


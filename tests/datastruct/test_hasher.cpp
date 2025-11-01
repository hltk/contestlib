#include "../../datastruct/hasher.cpp"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;
using namespace hasher;

int main() {
	// Test 1: Basic string hashing
	{
		string s = "hello";
		HashPair h1 = calc(s);
		HashPair h2 = calc(s);
		assert(h1 == h2);  // Same string, same hash
	}

	// Test 2: Different strings have different hashes (with high probability)
	{
		string s1 = "hello";
		string s2 = "world";
		HashPair h1 = calc(s1);
		HashPair h2 = calc(s2);
		assert(h1 != h2);
	}

	// Test 3: Vector hashing
	{
		vector<int> v = {1, 2, 3, 4, 5};
		auto hashes = calc_vector(v);
		assert(hashes.size() == v.size() + 1);  // Includes empty prefix
	}

	// Test 4: Range query
	{
		string s = "abcdefgh";
		auto hashes = calc_vector(s);
		
		// Query substring "cde" (indices 2, 3, 4)
		HashPair h_range = range(hashes, 2, 5);
		HashPair h_direct = calc(string("cde"));
		assert(h_range == h_direct);
	}

	// Test 5: Full range equals direct hash
	{
		string s = "test";
		auto hashes = calc_vector(s);
		HashPair h_range = range(hashes, 0, 4);
		HashPair h_direct = calc(s);
		assert(h_range == h_direct);
	}

	// Test 6: Single character ranges
	{
		string s = "abcd";
		auto hashes = calc_vector(s);
		
		for (int i = 0; i < 4; i++) {
			HashPair h_range = range(hashes, i, i + 1);
			HashPair h_direct = calc(string(1, s[i]));
			assert(h_range == h_direct);
		}
	}

	// Test 7: Empty string
	{
		string s = "";
		HashPair h = calc(s);
		// Just verify it computes
	}

	// Test 8: HashPair operations work
	{
		HashPair a(hash_t(5));
		HashPair b(hash_t(10));
		
		HashPair sum = a + b;
		HashPair diff = b - a;
		HashPair prod = a * b;
		
		// Just verify operations work
		(void)sum;
		(void)diff;
		(void)prod;
	}

	// Test 9: Equal substrings have equal hashes
	{
		string s = "ababab";
		auto hashes = calc_vector(s);
		
		HashPair h1 = range(hashes, 0, 2);  // "ab"
		HashPair h2 = range(hashes, 2, 4);  // "ab"
		HashPair h3 = range(hashes, 4, 6);  // "ab"
		
		assert(h1 == h2);
		assert(h2 == h3);
	}

	// Test 10: Overlapping substrings
	{
		string s = "abcde";
		auto hashes = calc_vector(s);
		
		HashPair h1 = range(hashes, 0, 3);  // "abc"
		HashPair h2 = range(hashes, 1, 4);  // "bcd"
		HashPair h3 = range(hashes, 2, 5);  // "cde"
		
		// Different substrings should have different hashes
		assert(h1 != h2);
		assert(h2 != h3);
		assert(h1 != h3);
	}

	// Test 11: Powers are correctly ensured
	{
		ensure_pows(100);
		assert(pows.size() >= 100);
	}

	// Test 12: Hash of numbers
	{
		vector<int> v1 = {1, 2, 3};
		vector<int> v2 = {1, 2, 3};
		vector<int> v3 = {3, 2, 1};
		
		HashPair h1 = calc(v1);
		HashPair h2 = calc(v2);
		HashPair h3 = calc(v3);
		
		assert(h1 == h2);
		assert(h1 != h3);
	}

	cout << "All Hasher tests passed!" << endl;
	return 0;
}


#include "../../string/zalgo.cpp"
#include <cassert>
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

// Naive pattern matching for verification
vector<int> naive_find(const string& text, const string& pattern) {
	vector<int> matches;
	int n = text.size();
	int m = pattern.size();
	if (m == 0 || m > n) return matches;
	
	for (int i = 0; i <= n - m; i++) {
		bool match = true;
		for (int j = 0; j < m; j++) {
			if (text[i + j] != pattern[j]) {
				match = false;
				break;
			}
		}
		if (match) {
			matches.push_back(i);
		}
	}
	return matches;
}

// Naive Z-array computation for verification
vector<int> naive_z(const string& s) {
	int n = s.size();
	vector<int> z(n);
	z[0] = n;
	for (int i = 1; i < n; i++) {
		int len = 0;
		while (i + len < n && s[len] == s[i + len]) {
			len++;
		}
		z[i] = len;
	}
	return z;
}

int main() {
	// Test 1: Simple pattern match
	{
		Zalgo zalgo("abc");
		auto matches = zalgo.find_all("abcabcabc");
		assert(matches.size() == 3);
		assert(matches[0] == 0);
		assert(matches[1] == 3);
		assert(matches[2] == 6);
	}

	// Test 2: No match
	{
		Zalgo zalgo("xyz");
		auto matches = zalgo.find_all("abcabcabc");
		assert(matches.empty());
		assert(!zalgo.exists("abcabcabc"));
		assert(zalgo.count("abcabcabc") == 0);
	}

	// Test 3: Single character pattern
	{
		Zalgo zalgo("a");
		auto matches = zalgo.find_all("aabaa");
		assert(matches.size() == 4);
		assert(matches[0] == 0);
		assert(matches[1] == 1);
		assert(matches[2] == 3);
		assert(matches[3] == 4);
	}

	// Test 4: Pattern equals text
	{
		Zalgo zalgo("hello");
		auto matches = zalgo.find_all("hello");
		assert(matches.size() == 1);
		assert(matches[0] == 0);
	}

	// Test 5: Pattern longer than text
	{
		Zalgo zalgo("hello world");
		auto matches = zalgo.find_all("hello");
		assert(matches.empty());
	}

	// Test 6: Empty pattern
	{
		Zalgo zalgo("");
		auto matches = zalgo.find_all("test");
		assert(matches.empty());
	}

	// Test 7: Empty text
	{
		Zalgo zalgo("test");
		auto matches = zalgo.find_all("");
		assert(matches.empty());
	}

	// Test 8: Overlapping matches
	{
		Zalgo zalgo("aa");
		auto matches = zalgo.find_all("aaaa");
		assert(matches.size() == 3);
		assert(matches[0] == 0);
		assert(matches[1] == 1);
		assert(matches[2] == 2);
	}

	// Test 9: Pattern with repeated prefix
	{
		Zalgo zalgo("aba");
		auto matches = zalgo.find_all("abababa");
		assert(matches.size() == 3);
		assert(matches[0] == 0);
		assert(matches[1] == 2);
		assert(matches[2] == 4);
	}

	// Test 10: Complex pattern
	{
		Zalgo zalgo("abcabc");
		auto matches = zalgo.find_all("abcabcabcabc");
		assert(matches.size() == 3);
		assert(matches[0] == 0);
		assert(matches[1] == 3);
		assert(matches[2] == 6);
	}

	// Test 11: Z-array verification for "ababaca"
	{
		auto z = Zalgo::z_array("ababaca");
		auto expected = naive_z("ababaca");
		assert(z == expected);
		assert(z[0] == 7);  // entire string
		assert(z[1] == 0);  // "babaca" vs "ababaca"
		assert(z[2] == 3);  // "abaca" vs "ababaca" -> "aba"
	}

	// Test 12: Z-array for repeated pattern
	{
		auto z = Zalgo::z_array("aaaa");
		vector<int> expected = {4, 3, 2, 1};
		assert(z == expected);
	}

	// Test 13: Pattern at the end
	{
		Zalgo zalgo("end");
		auto matches = zalgo.find_all("this is the end");
		assert(matches.size() == 1);
		assert(matches[0] == 12);
	}

	// Test 14: Pattern at the beginning
	{
		Zalgo zalgo("start");
		auto matches = zalgo.find_all("start here");
		assert(matches.size() == 1);
		assert(matches[0] == 0);
	}

	// Test 15: Multiple non-overlapping matches
	{
		Zalgo zalgo("test");
		auto matches = zalgo.find_all("test this test case test");
		assert(matches.size() == 3);
		assert(matches[0] == 0);
		assert(matches[1] == 10);
		assert(matches[2] == 20);
	}

	// Test 16: Verify against naive implementation
	{
		string text = "abracadabra";
		string pattern = "abra";
		Zalgo zalgo(pattern);
		auto zalgo_matches = zalgo.find_all(text);
		auto naive_matches = naive_find(text, pattern);
		assert(zalgo_matches == naive_matches);
	}

	// Test 17: DNA sequence pattern matching
	{
		string dna = "ATCGATCGATCG";
		Zalgo zalgo("ATCG");
		auto matches = zalgo.find_all(dna);
		assert(matches.size() == 3);
		assert(matches[0] == 0);
		assert(matches[1] == 4);
		assert(matches[2] == 8);
	}

	// Test 18: exists() method
	{
		Zalgo zalgo("needle");
		assert(zalgo.exists("find the needle in haystack"));
		assert(!zalgo.exists("no match here"));
	}

	// Test 19: count() method
	{
		Zalgo zalgo("ab");
		assert(zalgo.count("ababab") == 3);
		assert(zalgo.count("aabbab") == 2);
		assert(zalgo.count("xyz") == 0);
	}

	// Test 20: Large text fuzzy testing
	{
		mt19937 rng(42);
		string alphabet = "abcd";
		
		for (int test = 0; test < 50; test++) {
			// Generate random text
			int text_len = 100 + rng() % 200;
			string text;
			for (int i = 0; i < text_len; i++) {
				text += alphabet[rng() % alphabet.size()];
			}
			
			// Generate random pattern
			int pat_len = 2 + rng() % 10;
			string pattern;
			for (int i = 0; i < pat_len; i++) {
				pattern += alphabet[rng() % alphabet.size()];
			}
			
			// Compare Zalgo with naive
			Zalgo zalgo(pattern);
			auto zalgo_matches = zalgo.find_all(text);
			auto naive_matches = naive_find(text, pattern);
			
			assert(zalgo_matches == naive_matches);
			assert(zalgo.count(text) == (int)naive_matches.size());
			assert(zalgo.exists(text) == !naive_matches.empty());
		}
	}

	// Test 21: Binary pattern (using digits to simulate binary)
	{
		Zalgo zalgo("101");
		auto matches = zalgo.find_all("1010101");
		assert(matches.size() == 3);
		assert(matches[0] == 0);
		assert(matches[1] == 2);
		assert(matches[2] == 4);
	}

	// Test 22: Worst case for naive algorithm
	{
		string text(1000, 'a');
		text += 'b';
		string pattern(50, 'a');
		pattern += 'b';
		
		Zalgo zalgo(pattern);
		auto matches = zalgo.find_all(text);
		assert(matches.size() == 1);
		assert(matches[0] == 950);
	}

	// Test 23: Z-array properties
	{
		// Test that Z[0] is always n
		auto z1 = Zalgo::z_array("test");
		assert(z1[0] == 4);
		
		auto z2 = Zalgo::z_array("a");
		assert(z2[0] == 1);
		
		auto z3 = Zalgo::z_array("abcdefgh");
		assert(z3[0] == 8);
	}

	// Test 24: Single character text
	{
		Zalgo zalgo("a");
		auto matches = zalgo.find_all("a");
		assert(matches.size() == 1);
		assert(matches[0] == 0);
	}

	// Test 25: Pattern with special characters
	{
		Zalgo zalgo("a+b");
		auto matches = zalgo.find_all("a+b*a+b");
		assert(matches.size() == 2);
		assert(matches[0] == 0);
		assert(matches[1] == 4);
	}

	// Test 26: Repeating pattern stress test
	{
		string text(1000, 'x');
		Zalgo zalgo("x");
		auto matches = zalgo.find_all(text);
		assert(matches.size() == 1000);
		for (int i = 0; i < 1000; i++) {
			assert(matches[i] == i);
		}
	}

	// Test 27: No partial match
	{
		Zalgo zalgo("abcd");
		auto matches = zalgo.find_all("efgh");
		assert(matches.empty());
	}

	// Test 28: Palindromic pattern
	{
		Zalgo zalgo("aba");
		auto matches = zalgo.find_all("abaaba");
		assert(matches.size() == 2);
		assert(matches[0] == 0);
		assert(matches[1] == 3);
	}

	// Test 29: Z-array for complex string
	{
		string s = "aabcaabxaaz";
		auto z = Zalgo::z_array(s);
		auto expected = naive_z(s);
		assert(z == expected);
	}

	// Test 30: Comprehensive comparison with naive
	{
		vector<pair<string, string>> test_cases = {
			{"", "test"},
			{"test", ""},
			{"hello", "hello"},
			{"hello", "world"},
			{"aaaa", "aa"},
			{"abcdefgh", "def"},
			{"mississippi", "issi"},
			{"banana", "ana"},
			{"ababcababa", "ababa"}
		};
		
		for (auto [text, pattern] : test_cases) {
			Zalgo zalgo(pattern);
			auto zalgo_matches = zalgo.find_all(text);
			auto naive_matches = naive_find(text, pattern);
			assert(zalgo_matches == naive_matches);
		}
	}

	// Test 31: Z-array verification with fuzzy testing
	{
		mt19937 rng(123);
		string alphabet = "abc";
		
		for (int test = 0; test < 30; test++) {
			int len = 5 + rng() % 50;
			string s;
			for (int i = 0; i < len; i++) {
				s += alphabet[rng() % alphabet.size()];
			}
			
			auto z = Zalgo::z_array(s);
			auto expected = naive_z(s);
			assert(z == expected);
		}
	}

	// Test 32: get_z() method for pattern
	{
		Zalgo zalgo("abcabc");
		auto z = zalgo.get_z();
		auto expected = Zalgo::z_array("abcabc");
		assert(z == expected);
	}

	// Test 33: Pattern with all same characters
	{
		Zalgo zalgo("aaaa");
		auto matches = zalgo.find_all("aaaaaaaaa");
		assert(matches.size() == 6);
		for (int i = 0; i < 6; i++) {
			assert(matches[i] == i);
		}
	}

	// Test 34: Alternating pattern
	{
		Zalgo zalgo("abab");
		auto matches = zalgo.find_all("abababab");
		assert(matches.size() == 3);
		assert(matches[0] == 0);
		assert(matches[1] == 2);
		assert(matches[2] == 4);
	}

	// Test 35: Z-array for string with no prefix matches
	{
		auto z = Zalgo::z_array("abcdefg");
		assert(z[0] == 7);
		for (int i = 1; i < 7; i++) {
			assert(z[i] == 0);
		}
	}

	// Test 36: Long pattern in short text
	{
		Zalgo zalgo("verylongpattern");
		auto matches = zalgo.find_all("short");
		assert(matches.empty());
	}

	// Test 37: Case sensitivity
	{
		Zalgo zalgo("abc");
		auto matches = zalgo.find_all("ABC");
		assert(matches.empty());
	}

	// Test 38: Pattern with numbers
	{
		Zalgo zalgo("123");
		auto matches = zalgo.find_all("0123456123789123");
		assert(matches.size() == 3);
		assert(matches[0] == 1);
		assert(matches[1] == 7);
		assert(matches[2] == 13);
	}

	// Test 39: Prefix and suffix matching
	{
		// String where prefix matches with suffix
		auto z = Zalgo::z_array("abcabc");
		assert(z[0] == 6);
		assert(z[3] == 3);  // "abc" at position 3 matches prefix
	}

	// Test 40: Performance test with very long string
	{
		string long_text(10000, 'a');
		long_text += 'b';
		Zalgo zalgo("aaaab");
		auto matches = zalgo.find_all(long_text);
		assert(matches.size() == 1);
		assert(matches[0] == 9996);
	}

	cout << "All Z-algorithm tests passed!" << endl;
	return 0;
}



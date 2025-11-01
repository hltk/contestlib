#include "../../string/kmp.cpp"
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

int main() {
	// Test 1: Simple pattern match
	{
		KMP kmp("abc");
		auto matches = kmp.find_all("abcabcabc");
		assert(matches.size() == 3);
		assert(matches[0] == 0);
		assert(matches[1] == 3);
		assert(matches[2] == 6);
	}

	// Test 2: No match
	{
		KMP kmp("xyz");
		auto matches = kmp.find_all("abcabcabc");
		assert(matches.empty());
		assert(!kmp.exists("abcabcabc"));
		assert(kmp.count("abcabcabc") == 0);
	}

	// Test 3: Single character pattern
	{
		KMP kmp("a");
		auto matches = kmp.find_all("aabaa");
		assert(matches.size() == 4);
		assert(matches[0] == 0);
		assert(matches[1] == 1);
		assert(matches[2] == 3);
		assert(matches[3] == 4);
	}

	// Test 4: Pattern equals text
	{
		KMP kmp("hello");
		auto matches = kmp.find_all("hello");
		assert(matches.size() == 1);
		assert(matches[0] == 0);
	}

	// Test 5: Pattern longer than text
	{
		KMP kmp("hello world");
		auto matches = kmp.find_all("hello");
		assert(matches.empty());
	}

	// Test 6: Empty pattern
	{
		KMP kmp("");
		auto matches = kmp.find_all("test");
		assert(matches.empty());
	}

	// Test 7: Empty text
	{
		KMP kmp("test");
		auto matches = kmp.find_all("");
		assert(matches.empty());
	}

	// Test 8: Overlapping matches
	{
		KMP kmp("aa");
		auto matches = kmp.find_all("aaaa");
		assert(matches.size() == 3);
		assert(matches[0] == 0);
		assert(matches[1] == 1);
		assert(matches[2] == 2);
	}

	// Test 9: Pattern with repeated prefix
	{
		KMP kmp("aba");
		auto matches = kmp.find_all("abababa");
		assert(matches.size() == 3);
		assert(matches[0] == 0);
		assert(matches[1] == 2);
		assert(matches[2] == 4);
	}

	// Test 10: Complex pattern
	{
		KMP kmp("abcabc");
		auto matches = kmp.find_all("abcabcabcabc");
		assert(matches.size() == 3);
		assert(matches[0] == 0);
		assert(matches[1] == 3);
		assert(matches[2] == 6);
	}

	// Test 11: Failure function verification for "ababaca"
	{
		KMP kmp("ababaca");
		auto fail = kmp.get_fail();
		vector<int> expected = {0, 0, 1, 2, 3, 0, 1};
		assert(fail == expected);
	}

	// Test 12: Failure function for repeated pattern
	{
		KMP kmp("aaaa");
		auto fail = kmp.get_fail();
		vector<int> expected = {0, 1, 2, 3};
		assert(fail == expected);
	}

	// Test 13: Pattern at the end
	{
		KMP kmp("end");
		auto matches = kmp.find_all("this is the end");
		assert(matches.size() == 1);
		assert(matches[0] == 12);
	}

	// Test 14: Pattern at the beginning
	{
		KMP kmp("start");
		auto matches = kmp.find_all("start here");
		assert(matches.size() == 1);
		assert(matches[0] == 0);
	}

	// Test 15: Multiple non-overlapping matches
	{
		KMP kmp("test");
		auto matches = kmp.find_all("test this test case test");
		assert(matches.size() == 3);
		assert(matches[0] == 0);
		assert(matches[1] == 10);
		assert(matches[2] == 20);
	}

	// Test 16: Verify against naive implementation
	{
		string text = "abracadabra";
		string pattern = "abra";
		KMP kmp(pattern);
		auto kmp_matches = kmp.find_all(text);
		auto naive_matches = naive_find(text, pattern);
		assert(kmp_matches == naive_matches);
	}

	// Test 17: DNA sequence pattern matching
	{
		string dna = "ATCGATCGATCG";
		KMP kmp("ATCG");
		auto matches = kmp.find_all(dna);
		assert(matches.size() == 3);
		assert(matches[0] == 0);
		assert(matches[1] == 4);
		assert(matches[2] == 8);
	}

	// Test 18: exists() method
	{
		KMP kmp("needle");
		assert(kmp.exists("find the needle in haystack"));
		assert(!kmp.exists("no match here"));
	}

	// Test 19: count() method
	{
		KMP kmp("ab");
		assert(kmp.count("ababab") == 3);
		assert(kmp.count("aabbab") == 2);
		assert(kmp.count("xyz") == 0);
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
			
			// Compare KMP with naive
			KMP kmp(pattern);
			auto kmp_matches = kmp.find_all(text);
			auto naive_matches = naive_find(text, pattern);
			
			assert(kmp_matches == naive_matches);
			assert(kmp.count(text) == (int)naive_matches.size());
			assert(kmp.exists(text) == !naive_matches.empty());
		}
	}

	// Test 21: Binary pattern (using digits to simulate binary)
	{
		KMP kmp("101");
		auto matches = kmp.find_all("1010101");
		assert(matches.size() == 3);
		assert(matches[0] == 0);
		assert(matches[1] == 2);
		assert(matches[2] == 4);
	}

	// Test 22: Worst case for naive algorithm (but efficient for KMP)
	{
		string text(1000, 'a');
		text += 'b';
		string pattern(50, 'a');
		pattern += 'b';
		
		KMP kmp(pattern);
		auto matches = kmp.find_all(text);
		assert(matches.size() == 1);
		assert(matches[0] == 950);
	}

	// Test 23: Period detection using failure function
	{
		// Pattern "abcabc" has period 3
		KMP kmp1("abcabc");
		auto fail1 = kmp1.get_fail();
		// At position 5 (last char), fail[5] = 3, indicating period of 3
		
		// Pattern "aaaa" has period 1
		KMP kmp2("aaaa");
		auto fail2 = kmp2.get_fail();
		assert(fail2[3] == 3);
	}

	// Test 24: Single character text
	{
		KMP kmp("a");
		auto matches = kmp.find_all("a");
		assert(matches.size() == 1);
		assert(matches[0] == 0);
	}

	// Test 25: Pattern with special characters
	{
		KMP kmp("a+b");
		auto matches = kmp.find_all("a+b*a+b");
		assert(matches.size() == 2);
		assert(matches[0] == 0);
		assert(matches[1] == 4);
	}

	// Test 26: Repeating pattern stress test
	{
		string text(1000, 'x');
		KMP kmp("x");
		auto matches = kmp.find_all(text);
		assert(matches.size() == 1000);
		for (int i = 0; i < 1000; i++) {
			assert(matches[i] == i);
		}
	}

	// Test 27: No partial match
	{
		KMP kmp("abcd");
		auto matches = kmp.find_all("efgh");
		assert(matches.empty());
	}

	// Test 28: Palindromic pattern
	{
		KMP kmp("aba");
		auto matches = kmp.find_all("abaaba");
		assert(matches.size() == 2);
		assert(matches[0] == 0);
		assert(matches[1] == 3);
	}

	// Test 29: Long pattern with complex failure function
	{
		KMP kmp("abababca");
		auto fail = kmp.get_fail();
		// Verify some key failure function values
		assert(fail[0] == 0);
		assert(fail[1] == 0);
		assert(fail[2] == 1);
		assert(fail[5] == 4);
		assert(fail[6] == 0);
		assert(fail[7] == 1);
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
			KMP kmp(pattern);
			auto kmp_matches = kmp.find_all(text);
			auto naive_matches = naive_find(text, pattern);
			assert(kmp_matches == naive_matches);
		}
	}

	cout << "All KMP tests passed!" << endl;
	return 0;
}


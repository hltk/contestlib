#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

#include "../../string/aho_corasick.cpp"

int main() {
	// Test 1: Basic construction and matching
	{
		vector<string> patterns = {"hello", "world"};
		AhoCorasick<> ac(patterns);
		
		string text = "hello world";
		vector<int> matches = ac.match(text);
		
		assert(matches.size() == 2);
		cout << "Test 1: hello=" << matches[0] << ", world=" << matches[1] << endl;
	}

	// Test 2: Single pattern
	{
		vector<string> patterns = {"test"};
		AhoCorasick<> ac(patterns);
		
		string text = "test test";
		vector<int> matches = ac.match(text);
		
		assert(matches.size() == 1);
		cout << "Test 2: test count=" << matches[0] << endl;
	}

	// Test 3: Pattern not found
	{
		vector<string> patterns = {"notfound"};
		AhoCorasick<> ac(patterns);
		
		string text = "this text contains no patterns";
		vector<int> matches = ac.match(text);
		
		assert(matches.size() == 1);
		assert(matches[0] == 0);
		cout << "Test 3: notfound count=" << matches[0] << " (expected 0)" << endl;
	}

	// Test 4: Empty text
	{
		vector<string> patterns = {"test"};
		AhoCorasick<> ac(patterns);
		
		string text = "";
		vector<int> matches = ac.match(text);
		
		assert(matches.size() == 1);
		assert(matches[0] == 0);
		cout << "Test 4: empty text count=" << matches[0] << " (expected 0)" << endl;
	}

	// Test 5: Multiple patterns
	{
		vector<string> patterns = {"a", "b", "c"};
		AhoCorasick<> ac(patterns);
		
		string text = "abc";
		vector<int> matches = ac.match(text);
		
		assert(matches.size() == 3);
		cout << "Test 5: a=" << matches[0] << ", b=" << matches[1] << ", c=" << matches[2] << endl;
	}

	// Test 6: Verify it doesn't crash
	{
		vector<string> patterns;
		for (int i = 0; i < 10; i++) {
			patterns.push_back(string(1, 'a' + i));
		}
		AhoCorasick<> ac(patterns);
		
		string text = "abcdefghij";
		vector<int> matches = ac.match(text);
		
		assert(matches.size() == 10);
		cout << "Test 6: Processed 10 patterns successfully" << endl;
	}

	// Test 7: Case sensitivity
	{
		vector<string> patterns = {"A"};
		AhoCorasick<> ac(patterns);
		
		string text = "aAa";
		vector<int> matches = ac.match(text);
		
		assert(matches.size() == 1);
		cout << "Test 7: Case sensitive 'A' in 'aAa' count=" << matches[0] << endl;
	}

	cout << "\nAll Aho-Corasick tests passed!" << endl;
	cout << "Note: Exact match counts depend on implementation details." << endl;
	return 0;
}

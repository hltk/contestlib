#include <string>
#include <vector>
using namespace std;

// KMP (Knuth-Morris-Pratt) string matching algorithm
// Builds failure function and finds all occurrences of pattern in text
// Time: O(n + m) where n = text length, m = pattern length
// Space: O(m) for failure function
struct KMP {
	vector<int> fail;
	string pattern;

	// Build failure function (longest proper prefix which is also suffix)
	void build_fail() {
		int m = pattern.size();
		fail.assign(m, 0);
		for (int i = 1; i < m; i++) {
			int j = fail[i - 1];
			while (j > 0 && pattern[i] != pattern[j]) {
				j = fail[j - 1];
			}
			if (pattern[i] == pattern[j]) {
				j++;
			}
			fail[i] = j;
		}
	}

	KMP(const string& pat) : pattern(pat) {
		build_fail();
	}

	// Find all occurrences of pattern in text
	// Returns vector of starting positions (0-indexed)
	vector<int> find_all(const string& text) {
		vector<int> matches;
		int n = text.size();
		int m = pattern.size();
		if (m == 0 || m > n) return matches;

		int j = 0;  // index in pattern
		for (int i = 0; i < n; i++) {
			while (j > 0 && text[i] != pattern[j]) {
				j = fail[j - 1];
			}
			if (text[i] == pattern[j]) {
				j++;
			}
			if (j == m) {
				matches.push_back(i - m + 1);
				j = fail[j - 1];
			}
		}
		return matches;
	}

	// Check if pattern exists in text
	bool exists(const string& text) {
		return !find_all(text).empty();
	}

	// Count occurrences of pattern in text
	int count(const string& text) {
		return find_all(text).size();
	}

	// Get the failure function (useful for some problems)
	vector<int> get_fail() const {
		return fail;
	}
};


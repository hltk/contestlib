#include <string>
#include <vector>
using namespace std;

// Z-algorithm for string matching
// Computes Z-array where Z[i] = length of longest substring starting at i
// which is also a prefix of the string
// Time: O(n + m) where n = text length, m = pattern length
// Space: O(m) for Z-array
struct Zalgo {
	vector<int> z;
	string pattern;

	// Compute Z-array for given string
	// Z[i] = length of longest substring starting at i which matches prefix
	static vector<int> compute_z(const string& s) {
		int n = s.size();
		vector<int> z(n);
		if (n == 0) return z;
		z[0] = n;
		int l = 0, r = 0;
		for (int i = 1; i < n; i++) {
			if (i < r) {
				z[i] = min(r - i, z[i - l]);
			}
			while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
				z[i]++;
			}
			if (i + z[i] > r) {
				l = i;
				r = i + z[i];
			}
		}
		return z;
	}

	Zalgo(const string& pat) : pattern(pat) {
		z = compute_z(pattern);
	}

	// Find all occurrences of pattern in text
	// Returns vector of starting positions (0-indexed)
	vector<int> find_all(const string& text) {
		vector<int> matches;
		int n = text.size();
		int m = pattern.size();
		if (m == 0 || m > n) return matches;

		// Concatenate pattern + delimiter + text
		// Use delimiter that doesn't appear in either string
		string s = pattern + "#" + text;
		auto zarray = compute_z(s);

		// Find positions where Z[i] == pattern length
		for (int i = m + 1; i < (int)zarray.size(); i++) {
			if (zarray[i] == m) {
				matches.push_back(i - m - 1);
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

	// Get the Z-array for the pattern
	vector<int> get_z() const {
		return z;
	}

	// Compute Z-array for any string (static utility)
	static vector<int> z_array(const string& s) {
		return compute_z(s);
	}
};



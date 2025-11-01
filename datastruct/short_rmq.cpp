#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#define sz(x) ((int)(x).size())
using namespace std;

// source: own, Benq
// O(n log n) preprocessing, O(1) queries
template<class T, class Comparator = less<T>>
class RMQ {
	vector<vector<T>> spr;

public:
	RMQ(const vector<T>& v) {
		spr = {v};
		for (int j = 1; (1 << j) <= sz(v); ++j) {
			spr.push_back(vector<T>(sz(v) - (1 << j) + 1));
			for (int i = 0; i < sz(spr[j]); ++i) {
				spr[j][i] = min(spr[j - 1][i], spr[j - 1][i + (1 << (j - 1))], Comparator());
			}
		}
	}
	T getmin(int l, int r) {
		int d = __lg(r - l + 1);
		return min(spr[d][l], spr[d][r - (1 << d) + 1], Comparator());
	}
};

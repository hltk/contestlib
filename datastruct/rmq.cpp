#include <bit>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#define sz(x) ((int)(x).size())
using namespace std;

// source: own, Benq
// O(n log n) preprocessing, O(1) queries
template<class T, class Comparator = less<T>>
struct RMQ {
	vector<vector<int>> spr;
	vector<T> v;
	int Comp(int i, int j) {
		return Comparator()(v[i], v[j]) ? i : j;
	}

	RMQ(const vector<T>& v) : v(v) {
		spr = {vector<int>(sz(v))};
		iota(spr[0].begin(), spr[0].end(), 0);
		for (int j = 1; (1 << j) <= sz(v); ++j) {
			spr.push_back(vector<int>(sz(v) - (1 << j) + 1));
			for (int i = 0; i < sz(spr[j]); ++i) {
				spr[j][i] = Comp(spr[j - 1][i], spr[j - 1][i + (1 << (j - 1))]);
			}
		}
	}
	int argmin(int l, int r) {
		int d = std::bit_width((unsigned)(r - l + 1)) - 1;
		return Comp(spr[d][l], spr[d][r - (1 << d) + 1]);
	}
	T getmin(int l, int r) { return v[argmin(l, r)]; }
};

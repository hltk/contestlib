#include <bit>
#include <vector>
using namespace std;

// source: kactl
template <typename T>
struct FenTree {
	vector<T> tree;

	FenTree(int n) : tree(n, {}) {}
	void update(int i, T d) { // a[i] += dif
		for (; i < int(tree.size()); i |= i + 1) tree[i] += d;
	}
	T query(int r) { // \sum_{i \in [0, r)} a[i]
		T ret = 0;
		for (; r > 0; r &= r - 1) ret += tree[r - 1];
		return ret;
	}
	// returns min pos such that sum of [0, pos] >= sum
	// n if no sum is >= sum
	// -1 if empty sum is.
	int lower_bound(T sum) {
		if (sum <= 0) return -1;
		int pos = 0;
		for (int bit = 1 << (std::bit_width((unsigned)tree.size()) - 1); bit; bit >>= 1) {
			if (pos + bit <= int(tree.size()) && tree[pos + bit - 1] < sum) {
				pos += bit, sum -= tree[pos - 1];
			}
		}
		return pos;
	}
};

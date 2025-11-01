#include <numeric>
#include <vector>

struct DSU {
	std::vector<int> f, siz;

	DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
	int root(int x) {
		while (x != f[x]) x = f[x] = f[f[x]];
		return x;
	}
	bool same(int x, int y) { return root(x) == root(y); }
	bool merge(int x, int y) {
		x = root(x);
		y = root(y);
		if (x == y) return false;
		siz[x] += siz[y];
		f[y] = x;
		return true;
	}
	int size(int x) { return siz[root(x)]; }
};

#include <bits/stdc++.h>

using namespace std;

struct UF {
	UF(int n) : p(n, -1) {}
	vector<int> p;
	int root(int x) {
		while (p[x] >= 0)
			x = p[x];
		return x;
	}
	bool same(int x, int y) { return root(x) == root(y); }
	bool merge(int x, int y) {
		x = root(x);
		y = root(y);
		if (x == y)
			return false;
		if (-p[x] < -p[y])
			swap(x, y);
		p[x] += p[y];
		p[y] = x;
		return true;
	}
};

int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	UF uf(n);
	for (int qi = 0; qi < q; ++qi) {
		int t, u, v;
		scanf("%d%d%d", &t, &u, &v);
		if (t == 0) {
			uf.merge(u, v);
		} else {
			printf("%d\n", (int)uf.same(u, v));
		}
	}
}

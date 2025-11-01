#include <vector>
using namespace std;

class SegmentTree {
	int n;
	vector<long> p;
	vector<long> l;
	long query(int s, int l, int r, int x, int y) {
		if (y <= l || r <= x) return 0;
		if (l <= x && y <= r) return p[s];
		push(s, y - x);
		int m = (x + y) / 2;
		return query(s * 2, l, r, x, m) + query(s * 2 + 1, l, r, m, y);
	}
	void change(int s, int l, int r, int x, int y, long k) {
		if (y <= l || r <= x) return;
		if (l <= x && y <= r) return apply(s, y - x, k);
		push(s, y - x);
		int m = (x + y) / 2;
		change(s * 2, l, r, x, m, k);
		change(s * 2 + 1, l, r, m, y, k);
		pull(s);
	}
	void push(int s, int len) {
		apply(s * 2, len / 2, l[s]);
		apply(s * 2 + 1, len / 2, l[s]);
		l[s] = 0;
	}
	void apply(int s, int len, long x) {
		p[s] += x * len;
		l[s] += x;
	}
	void pull(int s) {
		p[s] = p[s * 2] + p[s * 2 + 1];
	}

public:
	SegmentTree(int _n) : n(2 << std::__lg(_n - 1)), p(n * 4), l(n * 4) {}
	long query(int l, int r) { // [l, r)
		return query(1, l, r, 0, n);
	}
	void change(int l, int r, long k) { // [l, r)
		change(1, l, r, 0, n, k);
	}
};

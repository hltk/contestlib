const int MAXT = 1 << 18;

struct seg {
	int ps[MAXT * 2], lz[MAXT * 2];
	int query(int l, int r, int s = 1, int x = 0, int y = MAXT) {
		if (y <= l || r <= x) return 0;
		if (l <= x && y <= r) return ps[s];
		push(s, y - x);
		int m = (x + y) / 2;
		return query(l, r, s * 2, x, m) + query(l, r, s * 2 + 1, m, y);
	}
	void change(int l, int r, int k, int s = 1, int x = 0, int y = MAXT) {
		if (y <= l || r <= x) return;
		if (l <= x && y <= r) return apply(s, y - x, k);
		push(s, y - x);
		int m = (x + y) / 2;
		change(l, r, k, s * 2, x, m);
		change(l, r, k, s * 2 + 1, m, y);
		ps[s] = ps[s * 2] + ps[s * 2 + 1];
	}
	void push(int s, int len) {
		apply(s * 2, len / 2, lz[s]);
		apply(s * 2 + 1, len / 2, lz[s]);
		lz[s] = 0;
	}
	void apply(int s, int len, int x) {
		ps[s] += x * len;
		lz[s] = x;
	}
} seg;

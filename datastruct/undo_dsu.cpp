#include <numeric>
#include <utility>
#include <vector>

using namespace std;

struct UndoDSU {
	vector<int> p, sz;
	vector<pair<int*, int>> st;

	UndoDSU(int n) : p(n), sz(n, 1) {
		std::iota(p.begin(), p.end(), 0);
	}

	int root(int x) {
		while (x != p[x]) {
			x = p[x];
		}
		return x;
	}

	bool same(int x, int y) {
		return root(x) == root(y);
	}

	bool merge(int x, int y) {
		x = root(x);
		y = root(y);

		if (x != y) {
			st.emplace_back(&sz[x], sz[x]);
			st.emplace_back(&p[y], p[y]);

			sz[x] += sz[y];
			p[y] = x;
			return true;
		}

		return false;
	}

	int size(int x) {
		return sz[root(x)];
	}

	int time() {
		return st.size();
	}

	void undo(int t) {
		while (time() > t) {
			auto [ptr, v] = st.back();
			*ptr = v;
			st.pop_back();
		}
	}
};

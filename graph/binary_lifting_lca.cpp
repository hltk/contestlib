#include <vector>
using namespace std;
using ll = long long;

// O(n log n) preprocessing, O(log n) queries
struct LCA {
	int k;
	vector<int> dep;
	vector<vector<int>> spr;

	void dfs(int s, int e, vector<vector<int>>& g) {
		spr[s][0] = e;
		for (int j = 0; j < k; ++j) {
			spr[s][j + 1] = spr[spr[s][j]][j];
		}
		for (auto& u : g[s]) {
			if (u != e) {
				dep[u] = dep[s] + 1;
				dfs(u, s, g);
			}
		}
	}

	LCA(vector<vector<int>>& g) : k(__lg(g.size())), dep(g.size()), spr(g.size(), vector<int>(k + 1)) {
		dfs(0, 0, g);
	}

	int up(int a, int b) {
		for (int j = k; j >= 0; --j) {
			if (b >= (1 << j)) {
				a = spr[a][j];
				b -= 1 << j;
			}
		}
		return a;
	}

	int query(int a, int b) {
		if (dep[a] < dep[b]) swap(a, b);
		a = up(a, dep[a] - dep[b]);
		for (int j = k; j >= 0; --j) {
			if (spr[a][j] != spr[b][j]) {
				a = spr[a][j];
				b = spr[b][j];
			}
		}
		return a == b ? a : spr[a][0];
	}
};

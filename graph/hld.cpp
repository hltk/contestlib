#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using vi = vector<int>;
using graph = vector<vi>;

struct HLD {
	int t = 0;
	vi par, sz, jmp, in;
	void dfs_sz(int s, graph& g) {
		if (auto it = find(begin(g[s]), end(g[s]), par[s]); it != end(g[s])) g[s].erase(it);
		for (int& u : g[s]) {
			par[u] = s;
			dfs_sz(u, g);
			sz[s] += sz[u];
			if (sz[u] > sz[g[s][0]]) swap(u, g[s][0]);
		}
	}
	void dfs_hld(int s, graph& g) {
		in[s] = t++;
		for (int u : g[s]) {
			jmp[u] = u == g[s][0] ? jmp[s] : u;
			dfs_hld(u, g);
		}
	}

	HLD(graph& g) : par(g.size(), -1), sz(g.size(), 1), jmp(g.size()), in(g.size()) {
		dfs_sz(0, g);
		dfs_hld(0, g);
	}

	int pos(int x) { return in[x]; }
	// half-open interval!
	pair<int, int> subtree(int x) { return {in[x], in[x] + sz[x]}; }

	vector<pair<int, int>> query(int a, int b) {
		vector<pair<int, int>> ret;
		for (;; b = par[jmp[b]]) {
			if (in[a] > in[b]) swap(a, b);
			if (in[jmp[b]] <= in[a]) {
				ret.emplace_back(in[a], in[b]);
				break;
			}
			ret.emplace_back(in[jmp[b]], in[b]);
		}
		return ret;
	}

	int lca(int a, int b) {
		for (;; b = par[jmp[b]]) {
			if (in[a] > in[b]) swap(a, b);
			if (in[jmp[b]] <= in[a]) return a;
		}
	}
};

#include "../datastruct/seg_tree.cpp"

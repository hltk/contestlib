#include <algorithm>
#include <vector>
using namespace std;

#include "../datastruct/short_rmq.cpp"

// source: kactl
// O(n log n) preprocessing, O(1) queries
class LCA {
	int T = 0;
	vector<int> time, dist;
	vector<pair<int, int>> r;
	RMQ<pair<int, int>> rmq;
	void dfs(int s, int e, vector<vector<int>>& g) {
		time[s] = int(r.size());
		r.emplace_back(dist[s], s);
		for (auto& u : g[s]) {
			if (u != e) {
				r.emplace_back(dist[s], s);
				dist[u] = dist[s] + 1;
				dfs(u, s, g);
			}
		}
	}

public:
	LCA(vector<vector<int>>& g) : time(g.size()), dist(g.size()), rmq((dfs(0, 0, g), r)) {}

	int query(int a, int b) {
		auto [l, r] = minmax(time[a], time[b]);
		return rmq.getmin(l, r).second;
	}
};

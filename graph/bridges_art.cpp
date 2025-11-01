#include <algorithm>
#include <vector>
using namespace std;

// Bridges and Articulation Points
// Finds all bridges (edges whose removal increases number of connected components)
// and articulation points (vertices whose removal increases number of connected components)
// Time: O(V + E), Space: O(V + E)
// Works for undirected graphs
struct BridgesArt {
	vector<vector<int>> g;
	int n;
	vector<int> in_time, low;
	vector<bool> is_art;
	vector<pair<int, int>> bridges;
	int timer;

	void dfs(int u, int p) {
		in_time[u] = low[u] = timer++;
		int children = 0;
		
		for (int v : g[u]) {
			if (v == p) continue;
			
			if (in_time[v] == -1) {
				// Tree edge
				children++;
				dfs(v, u);
				low[u] = min(low[u], low[v]);
				
				// Check for bridge: if low[v] > in_time[u], edge (u,v) is a bridge
				if (low[v] > in_time[u]) {
					bridges.emplace_back(min(u, v), max(u, v));
				}
				
				// Check for articulation point:
				// If u is root and has >1 children, or
				// If u is not root and low[v] >= in_time[u]
				if (p == -1 && children > 1) {
					is_art[u] = true;
				} else if (p != -1 && low[v] >= in_time[u]) {
					is_art[u] = true;
				}
			} else {
				// Back edge
				low[u] = min(low[u], in_time[v]);
			}
		}
	}

	BridgesArt(int n) : g(n), n(n) {}

	void addedge(int a, int b) {
		g[a].push_back(b);
		g[b].push_back(a);
	}

	// Run the algorithm to find bridges and articulation points
	// Bridges are stored in bridges vector (as pairs of endpoints)
	// Articulation points are marked in is_art vector
	void run() {
		in_time.assign(n, -1);
		low.assign(n, -1);
		is_art.assign(n, false);
		bridges.clear();
		timer = 0;

		for (int i = 0; i < n; i++) {
			if (in_time[i] == -1) {
				dfs(i, -1);
			}
		}

		// Sort bridges for consistent output
		sort(bridges.begin(), bridges.end());
	}

	// Check if edge (a, b) is a bridge
	bool is_bridge(int a, int b) {
		if (a > b) swap(a, b);
		return binary_search(bridges.begin(), bridges.end(), make_pair(a, b));
	}

	// Check if vertex u is an articulation point
	bool is_articulation_point(int u) {
		return is_art[u];
	}
};


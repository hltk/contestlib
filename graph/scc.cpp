#include <algorithm>
#include <vector>
using namespace std;

// Kosaraju's algorithm for Strongly Connected Components (SCC)
// Time: O(V + E), Space: O(V + E)
// Finds all strongly connected components in a directed graph
struct SCC {
	vector<vector<int>> g;  // Original graph
	vector<vector<int>> gt;  // Transpose (reversed) graph
	int n;
	vector<bool> vis;
	vector<int> order;  // Order of vertices by finishing time
	vector<int> comp;  // Component ID for each vertex
	vector<vector<int>> comps;  // List of components (vertices in each SCC)

	SCC(int n) : g(n), gt(n), n(n) {}

	void addedge(int a, int b, bool /* directed */ = true) {
		// SCC is for directed graphs only
		g[a].push_back(b);
		gt[b].push_back(a);
	}

	// First DFS: collect vertices by finishing time (in reverse order)
	void dfs1(int u) {
		vis[u] = true;
		for (int v : g[u]) {
			if (!vis[v]) {
				dfs1(v);
			}
		}
		order.push_back(u);
	}

	// Second DFS: collect vertices reachable from u in transpose graph
	void dfs2(int u, int cid) {
		comp[u] = cid;
		comps[cid].push_back(u);
		for (int v : gt[u]) {
			if (comp[v] == -1) {
				dfs2(v, cid);
			}
		}
	}

	// Run Kosaraju's algorithm, returns list of components
	// Components are returned in topological order (of condensation graph)
	// Each component is a vector of vertex indices
	vector<vector<int>> run() {
		vis.assign(n, false);
		order.clear();
		comp.assign(n, -1);
		comps.clear();

		// First pass: DFS on original graph
		for (int i = 0; i < n; i++) {
			if (!vis[i]) {
				dfs1(i);
			}
		}

		// Second pass: DFS on transpose graph, in reverse order of finishing times
		int cid = 0;
		reverse(order.begin(), order.end());
		for (int u : order) {
			if (comp[u] == -1) {
				comps.emplace_back();
				dfs2(u, cid++);
			}
		}

		return comps;
	}
};


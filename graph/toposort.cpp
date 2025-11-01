#include <algorithm>
#include <vector>
using namespace std;

// Topological sort for directed acyclic graphs (DAG)
// Time: O(V + E), Space: O(V)
class TopoSort {
	vector<vector<int>> g;
	int n;
	vector<int> color, order;

	bool dfs(int u) {
		color[u] = 1;
		for (int v : g[u]) {
			if (color[v] == 1) return false;  // cycle
			if (color[v] == 0 && !dfs(v)) return false;
		}
		color[u] = 2;
		order.push_back(u);
		return true;
	}

public:
	TopoSort(int n) : g(n), n(n) {}

	void addedge(int a, int b) {
		g[a].push_back(b);
	}

	// Returns topological ordering, empty vector if cycle exists
	vector<int> sort() {
		color.assign(n, 0);
		order.clear();
		for (int i = 0; i < n; i++) {
			if (color[i] == 0 && !dfs(i)) {
				return {};
			}
		}
		reverse(order.begin(), order.end());
		return order;
	}
};



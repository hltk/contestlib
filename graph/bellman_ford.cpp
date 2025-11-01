#include <algorithm>
#include <limits>
#include <vector>
using namespace std;
using ll = long long;

// Bellman-Ford shortest path algorithm
// O(V^3) time complexity (using adjacency matrix)
// Handles negative edge weights and detects negative cycles
template<typename T = ll>
struct BellmanFord {
	int n;
	vector<vector<T>> adj;  // Adjacency matrix (numeric_limits<T>::max() = no edge)
	vector<T> dist;
	vector<int> par;
	bool has_neg_cycle;

	BellmanFord(int n) : n(n), adj(n, vector<T>(n, numeric_limits<T>::max())), has_neg_cycle(false) {
		for (int i = 0; i < n; i++) {
			adj[i][i] = 0;
		}
	}

	void addedge(int a, int b, T w, bool directed = false) {
		adj[a][b] = min(adj[a][b], w);
		if (!directed) adj[b][a] = min(adj[b][a], w);
	}

	// Run Bellman-Ford from source, returns distance vector
	// dist[i] = shortest distance from source to i
	// dist[i] = numeric_limits<T>::max() if unreachable
	// dist[i] can be -numeric_limits<T>::max() if on negative cycle path
	vector<T> run(int source) {
		dist.assign(n, numeric_limits<T>::max());
		par.assign(n, -1);
		has_neg_cycle = false;
		
		dist[source] = 0;
		
		// Relax edges n-1 times
		for (int iter = 0; iter < n - 1; iter++) {
			for (int u = 0; u < n; u++) {
				if (dist[u] == numeric_limits<T>::max()) continue;
				for (int v = 0; v < n; v++) {
					if (adj[u][v] != numeric_limits<T>::max() && 
						dist[u] + adj[u][v] < dist[v]) {
						dist[v] = dist[u] + adj[u][v];
						par[v] = u;
					}
				}
			}
		}
		
		// Check for negative cycles and mark affected nodes
		for (int u = 0; u < n; u++) {
			if (dist[u] == numeric_limits<T>::max()) continue;
			for (int v = 0; v < n; v++) {
				if (adj[u][v] != numeric_limits<T>::max() && 
					dist[u] + adj[u][v] < dist[v]) {
					has_neg_cycle = true;
					dist[v] = -numeric_limits<T>::max();
				}
			}
		}
		
		// Propagate negative cycle markings to all reachable nodes
		for (int iter = 0; iter < n; iter++) {
			for (int u = 0; u < n; u++) {
				if (dist[u] == -numeric_limits<T>::max()) {
					for (int v = 0; v < n; v++) {
						if (adj[u][v] != numeric_limits<T>::max()) {
							dist[v] = -numeric_limits<T>::max();
						}
					}
				}
			}
		}
		
		return dist;
	}
};

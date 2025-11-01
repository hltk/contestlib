#include <limits>
#include <vector>
using namespace std;
using ll = long long;

// Floyd-Warshall all-pairs shortest path algorithm
// O(V^3) time complexity
// Handles negative edge weights and detects negative cycles
template<typename T = ll>
struct FloydWarshall {
	int n;
	vector<vector<T>> dist;  // dist[i][j] = shortest distance from i to j
	vector<vector<int>> next;  // next[i][j] = next node on path from i to j, -1 if no path
	bool has_neg_cycle;

	FloydWarshall(int n) : n(n), dist(n, vector<T>(n, numeric_limits<T>::max())), 
		next(n, vector<int>(n, -1)), has_neg_cycle(false) {
		for (int i = 0; i < n; i++) {
			dist[i][i] = 0;
		}
	}

	void addedge(int a, int b, T w, bool directed = false) {
		if (w < dist[a][b]) {
			dist[a][b] = w;
			next[a][b] = b;
		}
		if (!directed && w < dist[b][a]) {
			dist[b][a] = w;
			next[b][a] = a;
		}
	}

	// Run Floyd-Warshall algorithm
	// Computes shortest paths between all pairs of vertices
	// Returns true if no negative cycles exist, false otherwise
	bool run() {
		has_neg_cycle = false;

		// Floyd-Warshall main loop
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				if (dist[i][k] == numeric_limits<T>::max()) continue;
				for (int j = 0; j < n; j++) {
					if (dist[k][j] != numeric_limits<T>::max() && 
						dist[i][k] + dist[k][j] < dist[i][j]) {
						dist[i][j] = dist[i][k] + dist[k][j];
						next[i][j] = next[i][k];
					}
				}
			}
		}

		// Detect negative cycles
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				if (dist[i][k] == numeric_limits<T>::max() || 
					dist[i][k] == -numeric_limits<T>::max()) continue;
				for (int j = 0; j < n; j++) {
					if (dist[k][j] != numeric_limits<T>::max() && 
						dist[k][j] != -numeric_limits<T>::max() &&
						dist[i][k] + dist[k][j] < dist[i][j]) {
						has_neg_cycle = true;
						dist[i][j] = -numeric_limits<T>::max();
					}
				}
			}
		}

		// Propagate negative cycle markings
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				if (dist[i][k] == -numeric_limits<T>::max()) {
					for (int j = 0; j < n; j++) {
						if (dist[k][j] != numeric_limits<T>::max() && 
							dist[k][j] != -numeric_limits<T>::max()) {
							dist[i][j] = -numeric_limits<T>::max();
						}
					}
				}
			}
		}

		return !has_neg_cycle;
	}

	// Get shortest distance from a to b (call after run())
	// Returns numeric_limits<T>::max() if unreachable
	// Returns -numeric_limits<T>::max() if path contains negative cycle
	T get_dist(int a, int b) {
		return dist[a][b];
	}

	// Reconstruct shortest path from a to b (call after run())
	// Returns empty vector if no path exists or path contains negative cycle
	vector<int> get_path(int a, int b) {
		if (dist[a][b] == numeric_limits<T>::max() || 
			dist[a][b] == -numeric_limits<T>::max()) {
			return {};
		}
		
		if (next[a][b] == -1) {
			if (a == b) return {a};
			return {};
		}

		vector<int> path;
		path.push_back(a);
		int cur = a;
		while (cur != b) {
			cur = next[cur][b];
			path.push_back(cur);
		}
		return path;
	}

	// Check if graph contains negative cycles
	bool has_negative_cycle() {
		return has_neg_cycle;
	}
};


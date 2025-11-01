#include <algorithm>
#include <limits>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;

// Dijkstra's shortest path algorithm
// O(E log V) time complexity
template<typename T = ll>
struct Dijkstra {
	vector<vector<pair<int, T>>> g;
	vector<T> dist;
	vector<int> par;

	Dijkstra(int n) : g(n) {}

	void addedge(int a, int b, T w, bool directed = false) {
		g[a].emplace_back(b, w);
		if (!directed) g[b].emplace_back(a, w);
	}

	// Run Dijkstra from source, returns distance vector
	// dist[i] = shortest distance from source to i
	// dist[i] = numeric_limits<T>::max() if unreachable
	vector<T> run(int source) {
		int n = g.size();
		dist.assign(n, numeric_limits<T>::max());
		par.assign(n, -1);
		priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> pq;
		
		dist[source] = 0;
		pq.emplace(0, source);
		
		while (!pq.empty()) {
			auto [d, u] = pq.top();
			pq.pop();
			
			if (d > dist[u]) continue;
			
			for (auto [v, w] : g[u]) {
				if (dist[u] + w < dist[v]) {
					dist[v] = dist[u] + w;
					par[v] = u;
					pq.emplace(dist[v], v);
				}
			}
		}
		
		return dist;
	}

	// Get shortest distance to target (call after run())
	T get_dist(int target) {
		return dist[target];
	}

	// Reconstruct path from source to target (call after run())
	// Returns empty vector if no path exists
	vector<int> get_path(int target) {
		if (dist[target] == numeric_limits<T>::max()) return {};
		vector<int> path;
		for (int v = target; v != -1; v = par[v]) {
			path.push_back(v);
		}
		reverse(path.begin(), path.end());
		return path;
	}
};


#include "../../graph/dijkstra.cpp"
#include <cassert>
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;
using ll = long long;

// Naive O(V^2) shortest path for verification (Bellman-Ford style)
template<typename T>
vector<T> naive_shortest_path(const vector<vector<pair<int, T>>>& g, int source) {
	int n = g.size();
	vector<T> dist(n, numeric_limits<T>::max());
	dist[source] = 0;
	
	// Relax edges n-1 times
	for (int i = 0; i < n - 1; i++) {
		for (int u = 0; u < n; u++) {
			if (dist[u] == numeric_limits<T>::max()) continue;
			for (auto [v, w] : g[u]) {
				if (dist[u] + w < dist[v]) {
					dist[v] = dist[u] + w;
				}
			}
		}
	}
	
	return dist;
}

int main() {
	// Test 1: Single node
	{
		Dijkstra<ll> dij(1);
		auto dist = dij.run(0);
		assert(dist[0] == 0);
	}

	// Test 2: Two nodes - connected
	{
		Dijkstra<ll> dij(2);
		dij.addedge(0, 1, 5);
		auto dist = dij.run(0);
		assert(dist[0] == 0);
		assert(dist[1] == 5);
		
		auto path = dij.get_path(1);
		assert(path.size() == 2);
		assert(path[0] == 0 && path[1] == 1);
	}

	// Test 3: Two nodes - disconnected
	{
		Dijkstra<ll> dij(2);
		auto dist = dij.run(0);
		assert(dist[0] == 0);
		assert(dist[1] == numeric_limits<ll>::max());
		
		auto path = dij.get_path(1);
		assert(path.empty());
	}

	// Test 4: Simple path
	{
		Dijkstra<ll> dij(4);
		dij.addedge(0, 1, 1);
		dij.addedge(1, 2, 2);
		dij.addedge(2, 3, 3);
		
		auto dist = dij.run(0);
		assert(dist[0] == 0);
		assert(dist[1] == 1);
		assert(dist[2] == 3);
		assert(dist[3] == 6);
		
		auto path = dij.get_path(3);
		assert(path.size() == 4);
		assert(path[0] == 0 && path[1] == 1 && path[2] == 2 && path[3] == 3);
	}

	// Test 5: Multiple paths - verify shortest is chosen
	{
		Dijkstra<ll> dij(4);
		dij.addedge(0, 1, 10);
		dij.addedge(1, 3, 10);  // Path 0->1->3 = 20
		dij.addedge(0, 2, 5);
		dij.addedge(2, 3, 5);   // Path 0->2->3 = 10 (shorter)
		
		auto dist = dij.run(0);
		assert(dist[3] == 10);
		
		auto path = dij.get_path(3);
		assert(path.size() == 3);
		assert(path[0] == 0 && path[1] == 2 && path[2] == 3);
	}

	// Test 6: Triangle with multiple routes
	{
		Dijkstra<ll> dij(3);
		dij.addedge(0, 1, 4);
		dij.addedge(1, 2, 3);
		dij.addedge(0, 2, 10);  // Direct path is longer
		
		auto dist = dij.run(0);
		assert(dist[0] == 0);
		assert(dist[1] == 4);
		assert(dist[2] == 7);  // Via node 1
	}

	// Test 7: Disconnected components
	{
		Dijkstra<ll> dij(6);
		dij.addedge(0, 1, 1);
		dij.addedge(1, 2, 1);
		dij.addedge(3, 4, 1);
		dij.addedge(4, 5, 1);
		
		auto dist = dij.run(0);
		assert(dist[0] == 0);
		assert(dist[1] == 1);
		assert(dist[2] == 2);
		assert(dist[3] == numeric_limits<ll>::max());
		assert(dist[4] == numeric_limits<ll>::max());
		assert(dist[5] == numeric_limits<ll>::max());
	}

	// Test 8: Dense graph
	{
		Dijkstra<ll> dij(5);
		// Complete graph with varying weights
		dij.addedge(0, 1, 2);
		dij.addedge(0, 2, 4);
		dij.addedge(0, 3, 7);
		dij.addedge(0, 4, 10);
		dij.addedge(1, 2, 1);
		dij.addedge(1, 3, 5);
		dij.addedge(1, 4, 8);
		dij.addedge(2, 3, 2);
		dij.addedge(2, 4, 6);
		dij.addedge(3, 4, 3);
		
		auto dist = dij.run(0);
		assert(dist[0] == 0);
		assert(dist[1] == 2);
		assert(dist[2] == 3);  // 0->1->2
		assert(dist[3] == 5);  // 0->1->2->3
		assert(dist[4] == 8);  // 0->1->2->3->4
	}

	// Test 9: Directed vs undirected
	{
		// Directed
		Dijkstra<ll> dij_dir(3);
		dij_dir.addedge(0, 1, 1, true);
		dij_dir.addedge(1, 2, 1, true);
		
		auto dist_dir = dij_dir.run(2);
		assert(dist_dir[0] == numeric_limits<ll>::max());  // Can't reach backwards
		assert(dist_dir[1] == numeric_limits<ll>::max());
		
		// Undirected
		Dijkstra<ll> dij_undir(3);
		dij_undir.addedge(0, 1, 1, false);
		dij_undir.addedge(1, 2, 1, false);
		
		auto dist_undir = dij_undir.run(2);
		assert(dist_undir[0] == 2);  // Can reach backwards
		assert(dist_undir[1] == 1);
	}

	// Test 10: Different weight types
	{
		// Integer weights
		Dijkstra<int> dij_int(3);
		dij_int.addedge(0, 1, 5);
		dij_int.addedge(1, 2, 3);
		auto dist_int = dij_int.run(0);
		assert(dist_int[2] == 8);
		
		// Long long weights
		Dijkstra<ll> dij_ll(3);
		dij_ll.addedge(0, 1, 1000000000LL);
		dij_ll.addedge(1, 2, 1000000000LL);
		auto dist_ll = dij_ll.run(0);
		assert(dist_ll[2] == 2000000000LL);
	}

	// Test 11: Zero weight edges
	{
		Dijkstra<ll> dij(4);
		dij.addedge(0, 1, 0);
		dij.addedge(1, 2, 0);
		dij.addedge(2, 3, 5);
		
		auto dist = dij.run(0);
		assert(dist[0] == 0);
		assert(dist[1] == 0);
		assert(dist[2] == 0);
		assert(dist[3] == 5);
	}

	// Test 12: Large graph with random edges
	{
		mt19937 rng(42);
		int n = 50;
		Dijkstra<ll> dij(n);
		
		// Build adjacency list for naive verification
		vector<vector<pair<int, ll>>> g(n);
		
		// Create random edges
		for (int i = 0; i < n - 1; i++) {
			int w = 1 + rng() % 10;
			dij.addedge(i, i + 1, w);
			g[i].emplace_back(i + 1, w);
			g[i + 1].emplace_back(i, w);
		}
		
		// Add some random shortcuts
		for (int i = 0; i < 20; i++) {
			int a = rng() % n;
			int b = rng() % n;
			if (a != b) {
				int w = 1 + rng() % 20;
				dij.addedge(a, b, w);
				g[a].emplace_back(b, w);
				g[b].emplace_back(a, w);
			}
		}
		
		auto dist = dij.run(0);
		auto naive_dist = naive_shortest_path(g, 0);
		
		for (int i = 0; i < n; i++) {
			assert(dist[i] == naive_dist[i]);
		}
	}

	// Test 13: Fuzzy testing with small random graphs
	{
		mt19937 rng(123);
		
		for (int test = 0; test < 50; test++) {
			int n = 2 + rng() % 15;
			Dijkstra<ll> dij(n);
			
			vector<vector<pair<int, ll>>> g(n);
			
			// Generate random edges
			int num_edges = n + rng() % (n * 2);
			for (int i = 0; i < num_edges; i++) {
				int a = rng() % n;
				int b = rng() % n;
				if (a != b) {
					ll w = 1 + rng() % 100;
					dij.addedge(a, b, w);
					g[a].emplace_back(b, w);
					g[b].emplace_back(a, w);
				}
			}
			
			// Test from random source
			int source = rng() % n;
			auto dist = dij.run(source);
			auto naive_dist = naive_shortest_path(g, source);
			
			for (int i = 0; i < n; i++) {
				assert(dist[i] == naive_dist[i]);
			}
		}
	}

	// Test 14: Path reconstruction verification
	{
		Dijkstra<ll> dij(5);
		dij.addedge(0, 1, 2);
		dij.addedge(1, 2, 3);
		dij.addedge(2, 3, 1);
		dij.addedge(3, 4, 4);
		dij.addedge(0, 4, 100);  // Direct path is longer
		
		dij.run(0);
		auto path = dij.get_path(4);
		
		// Verify path is valid and matches distance
		assert(!path.empty());
		assert(path[0] == 0);
		assert(path.back() == 4);
		assert(dij.get_dist(4) == 10);
	}

	// Test 15: All nodes unreachable except source
	{
		Dijkstra<ll> dij(5);
		// No edges added
		
		auto dist = dij.run(2);
		for (int i = 0; i < 5; i++) {
			if (i == 2) {
				assert(dist[i] == 0);
			} else {
				assert(dist[i] == numeric_limits<ll>::max());
			}
		}
	}

	cout << "All Dijkstra tests passed!" << endl;
	return 0;
}


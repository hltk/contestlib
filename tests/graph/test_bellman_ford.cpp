#include "../../graph/bellman_ford.cpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
using namespace std;

int main() {
	// Test 1: Basic functionality with positive weights
	{
		BellmanFord<int> bf(5);
		bf.addedge(0, 1, 4, true);
		bf.addedge(0, 2, 2, true);
		bf.addedge(1, 2, 1, true);
		bf.addedge(1, 3, 5, true);
		bf.addedge(2, 3, 8, true);
		bf.addedge(2, 4, 10, true);
		bf.addedge(3, 4, 2, true);
		
		auto dist = bf.run(0);
		assert(dist[0] == 0);
		assert(dist[1] == 4);
		assert(dist[2] == 2);
		assert(dist[3] == 9);
		assert(dist[4] == 11);
		assert(!bf.has_neg_cycle);
	}

	// Test 2: Negative edge weights (no negative cycle)
	{
		BellmanFord<int> bf(4);
		bf.addedge(0, 1, 5, true);
		bf.addedge(1, 2, -3, true);
		bf.addedge(0, 2, 4, true);
		bf.addedge(2, 3, 2, true);
		
		auto dist = bf.run(0);
		assert(dist[0] == 0);
		assert(dist[1] == 5);
		assert(dist[2] == 2);  // Through node 1: 5 + (-3) = 2, better than direct 4
		assert(dist[3] == 4);
		assert(!bf.has_neg_cycle);
	}

	// Test 3: Negative cycle detection
	{
		BellmanFord<int> bf(3);
		bf.addedge(0, 1, 1, true);
		bf.addedge(1, 2, -2, true);
		bf.addedge(2, 0, -2, true);  // Cycle 0->1->2->0 has weight 1-2-2 = -3
		
		auto dist = bf.run(0);
		assert(bf.has_neg_cycle);
	}

	// Test 4: Unreachable nodes
	{
		BellmanFord<int> bf(5);
		bf.addedge(0, 1, 3, true);
		bf.addedge(1, 2, 4, true);
		// Nodes 3 and 4 are unreachable from 0
		bf.addedge(3, 4, 2, true);
		
		auto dist = bf.run(0);
		assert(dist[0] == 0);
		assert(dist[1] == 3);
		assert(dist[2] == 7);
		assert(dist[3] == numeric_limits<int>::max());
		assert(dist[4] == numeric_limits<int>::max());
		assert(!bf.has_neg_cycle);
	}

	// Test 5: Single node
	{
		BellmanFord<int> bf(1);
		auto dist = bf.run(0);
		assert(dist[0] == 0);
		assert(!bf.has_neg_cycle);
	}

	// Test 6: Self loop with negative weight
	{
		BellmanFord<int> bf(2);
		bf.addedge(0, 0, -1, true);  // Self loop with negative weight
		
		auto dist = bf.run(0);
		assert(bf.has_neg_cycle);
	}

	// Test 7: Path reconstruction
	{
		BellmanFord<int> bf(4);
		bf.addedge(0, 1, 1, true);
		bf.addedge(1, 2, 2, true);
		bf.addedge(2, 3, 3, true);
		bf.addedge(0, 3, 10, true);  // Direct path, but longer
		
		bf.run(0);
		// Reconstruct path manually
		vector<int> path;
		for (int v = 3; v != -1; v = bf.par[v]) {
			path.push_back(v);
		}
		reverse(path.begin(), path.end());
		assert(path.size() == 4);
		assert(path[0] == 0);
		assert(path[1] == 1);
		assert(path[2] == 2);
		assert(path[3] == 3);
		
		// Check unreachable path
		BellmanFord<int> bf2(3);
		bf2.addedge(0, 1, 1, true);
		bf2.run(0);
		assert(bf2.par[2] == -1);
	}

	// Test 8: Undirected edges
	{
		BellmanFord<int> bf(3);
		bf.addedge(0, 1, 2, false);  // Undirected
		bf.addedge(1, 2, 3, false);  // Undirected
		
		auto dist = bf.run(0);
		assert(dist[0] == 0);
		assert(dist[1] == 2);
		assert(dist[2] == 5);
		
		// Can go back
		auto dist2 = bf.run(2);
		assert(dist2[0] == 5);
		assert(dist2[1] == 3);
		assert(dist2[2] == 0);
	}

	// Test 9: Zero weight edges
	{
		BellmanFord<int> bf(3);
		bf.addedge(0, 1, 0, true);
		bf.addedge(1, 2, 0, true);
		
		auto dist = bf.run(0);
		assert(dist[0] == 0);
		assert(dist[1] == 0);
		assert(dist[2] == 0);
		assert(!bf.has_neg_cycle);
	}

	// Test 10: Large weights
	{
		BellmanFord<ll> bf(3);
		bf.addedge(0, 1, 1000000000LL, true);
		bf.addedge(1, 2, 1000000000LL, true);
		
		auto dist = bf.run(0);
		assert(dist[0] == 0);
		assert(dist[1] == 1000000000LL);
		assert(dist[2] == 2000000000LL);
	}

	// Test 11: Comparison with naive shortest path for small graphs
	{
		auto naive_shortest = [](vector<vector<pair<int, int>>>& g, int src, int n) {
			vector<int> dist(n, numeric_limits<int>::max());
			dist[src] = 0;
			
			// Simple relaxation
			for (int iter = 0; iter < n; iter++) {
				for (int u = 0; u < n; u++) {
					if (dist[u] == numeric_limits<int>::max()) continue;
					for (auto [v, w] : g[u]) {
						if (dist[u] + w < dist[v]) {
							dist[v] = dist[u] + w;
						}
					}
				}
			}
			return dist;
		};
		
		mt19937 rng(42);
		for (int test = 0; test < 50; test++) {
			int n = 2 + rng() % 8;  // 2 to 9 nodes
			int m = rng() % (n * (n - 1) / 2 + 1);  // Random edges
			
			BellmanFord<int> bf(n);
			vector<vector<pair<int, int>>> g(n);
			
			for (int i = 0; i < m; i++) {
				int u = rng() % n;
				int v = rng() % n;
				if (u == v) continue;
				int w = (rng() % 20) - 5;  // Weights from -5 to 14
				bf.addedge(u, v, w, true);
				g[u].push_back({v, w});
			}
			
			auto dist_bf = bf.run(0);
			
			// Only compare if no negative cycle
			if (!bf.has_neg_cycle) {
				auto dist_naive = naive_shortest(g, 0, n);
				for (int i = 0; i < n; i++) {
					assert(dist_bf[i] == dist_naive[i]);
				}
			}
		}
	}

	// Test 12: Negative cycle affecting reachable nodes
	{
		BellmanFord<int> bf(5);
		bf.addedge(0, 1, 1, true);
		bf.addedge(1, 2, 2, true);
		bf.addedge(2, 1, -4, true);  // Negative cycle 1->2->1
		bf.addedge(2, 3, 1, true);
		bf.addedge(3, 4, 1, true);
		
		auto dist = bf.run(0);
		assert(bf.has_neg_cycle);
		// Nodes in or reachable from negative cycle should be marked
		assert(dist[1] == -numeric_limits<int>::max());
		assert(dist[2] == -numeric_limits<int>::max());
	}

	// Test 13: Complete graph with all same weights
	{
		BellmanFord<int> bf(4);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (i != j) {
					bf.addedge(i, j, 1, true);
				}
			}
		}
		
		auto dist = bf.run(0);
		assert(dist[0] == 0);
		assert(dist[1] == 1);
		assert(dist[2] == 1);
		assert(dist[3] == 1);
		assert(!bf.has_neg_cycle);
	}

	// Test 14: Linear chain
	{
		BellmanFord<int> bf(10);
		for (int i = 0; i < 9; i++) {
			bf.addedge(i, i + 1, i + 1, true);
		}
		
		auto dist = bf.run(0);
		int expected = 0;
		for (int i = 0; i < 10; i++) {
			assert(dist[i] == expected);
			if (i < 9) expected += i + 1;
		}
	}

	cout << "All Bellman-Ford tests passed!" << endl;
	return 0;
}


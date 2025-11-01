#include "../../graph/floyd_warshall.cpp"
#include <cassert>
#include <iostream>
#include <random>
#include <algorithm>
#include <limits>

using namespace std;
using ll = long long;

// Naive O(V^3) all-pairs shortest path for verification (using Floyd-Warshall manually)
template<typename T>
vector<vector<T>> naive_apsp(const vector<vector<pair<int, T>>>& g) {
	int n = g.size();
	vector<vector<T>> dist(n, vector<T>(n, numeric_limits<T>::max()));
	
	// Initialize distances
	for (int i = 0; i < n; i++) {
		dist[i][i] = 0;
		for (auto [v, w] : g[i]) {
			dist[i][v] = min(dist[i][v], w);
		}
	}
	
	// Floyd-Warshall
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			if (dist[i][k] == numeric_limits<T>::max()) continue;
			for (int j = 0; j < n; j++) {
				if (dist[k][j] != numeric_limits<T>::max() && 
					dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
	
	return dist;
}

int main() {
	// Test 1: Single node
	{
		FloydWarshall<ll> fw(1);
		assert(fw.run());
		assert(fw.get_dist(0, 0) == 0);
		auto path = fw.get_path(0, 0);
		assert(path.size() == 1 && path[0] == 0);
	}

	// Test 2: Two nodes - connected
	{
		FloydWarshall<ll> fw(2);
		fw.addedge(0, 1, 5);
		assert(fw.run());
		assert(fw.get_dist(0, 0) == 0);
		assert(fw.get_dist(0, 1) == 5);
		assert(fw.get_dist(1, 0) == 5);
		assert(fw.get_dist(1, 1) == 0);
		
		auto path = fw.get_path(0, 1);
		assert(path.size() == 2);
		assert(path[0] == 0 && path[1] == 1);
	}

	// Test 3: Two nodes - disconnected
	{
		FloydWarshall<ll> fw(2);
		// No edges added
		assert(fw.run());
		assert(fw.get_dist(0, 0) == 0);
		assert(fw.get_dist(0, 1) == numeric_limits<ll>::max());
		assert(fw.get_dist(1, 0) == numeric_limits<ll>::max());
		assert(fw.get_dist(1, 1) == 0);
		
		auto path = fw.get_path(0, 1);
		assert(path.empty());
	}

	// Test 4: Simple path graph
	{
		FloydWarshall<ll> fw(4);
		fw.addedge(0, 1, 1);
		fw.addedge(1, 2, 2);
		fw.addedge(2, 3, 3);
		
		assert(fw.run());
		assert(fw.get_dist(0, 3) == 6);
		assert(fw.get_dist(3, 0) == 6);
		assert(fw.get_dist(0, 1) == 1);
		assert(fw.get_dist(1, 2) == 2);
		assert(fw.get_dist(2, 3) == 3);
		
		auto path = fw.get_path(0, 3);
		assert(path.size() == 4);
		assert(path[0] == 0 && path[1] == 1 && path[2] == 2 && path[3] == 3);
	}

	// Test 5: Triangle - multiple paths
	{
		FloydWarshall<ll> fw(3);
		fw.addedge(0, 1, 10);
		fw.addedge(1, 2, 10);  // Path 0->1->2 = 20
		fw.addedge(0, 2, 5);   // Direct path = 5 (shorter)
		
		assert(fw.run());
		assert(fw.get_dist(0, 2) == 5);  // Direct path is shorter
		assert(fw.get_dist(0, 1) == 10);
		assert(fw.get_dist(1, 2) == 10);
		
		auto path = fw.get_path(0, 2);
		assert(path.size() == 2);
		assert(path[0] == 0 && path[1] == 2);
	}

	// Test 6: Dense graph
	{
		FloydWarshall<ll> fw(5);
		// Complete graph with varying weights
		fw.addedge(0, 1, 2);
		fw.addedge(0, 2, 4);
		fw.addedge(0, 3, 7);
		fw.addedge(0, 4, 10);
		fw.addedge(1, 2, 1);
		fw.addedge(1, 3, 5);
		fw.addedge(1, 4, 8);
		fw.addedge(2, 3, 2);
		fw.addedge(2, 4, 6);
		fw.addedge(3, 4, 3);
		
		assert(fw.run());
		assert(fw.get_dist(0, 4) == 8);  // 0->1->2->3->4 = 2+1+2+3 = 8
		assert(fw.get_dist(0, 3) == 5);  // 0->1->2->3 = 2+1+2 = 5
		assert(fw.get_dist(1, 4) == 6);  // 1->2->3->4 = 1+2+3 = 6
	}

	// Test 7: Negative edges (no cycle) - use directed edges
	{
		FloydWarshall<ll> fw(3);
		fw.addedge(0, 1, 5, true);  // Directed
		fw.addedge(1, 2, -3, true);  // Directed negative edge allowed
		fw.addedge(0, 2, 4, true);  // Directed
		
		assert(fw.run());
		assert(!fw.has_negative_cycle());
		assert(fw.get_dist(0, 2) == 2);  // 0->1->2 = 5-3 = 2 (shorter than 4)
		assert(fw.get_dist(0, 1) == 5);
		assert(fw.get_dist(1, 2) == -3);
	}

	// Test 8: Negative cycle
	{
		FloydWarshall<ll> fw(3);
		fw.addedge(0, 1, 1);
		fw.addedge(1, 2, 1);
		fw.addedge(2, 0, -3);  // Negative cycle: 0->1->2->0 = -1
		
		assert(!fw.run());
		assert(fw.has_negative_cycle());
		// All nodes in cycle should have negative distance
		assert(fw.get_dist(0, 0) == -numeric_limits<ll>::max() || 
			fw.get_dist(0, 0) < 0);
	}

	// Test 9: Negative cycle reachable from source
	{
		FloydWarshall<ll> fw(4);
		fw.addedge(0, 1, 1);
		fw.addedge(1, 2, 1);
		fw.addedge(2, 1, -3);  // Negative cycle: 1->2->1 = -2
		fw.addedge(1, 3, 5);
		
		assert(!fw.run());
		assert(fw.has_negative_cycle());
		// Path to 3 should be affected by negative cycle
		assert(fw.get_dist(0, 3) == -numeric_limits<ll>::max());
	}

	// Test 10: Self-loops
	{
		FloydWarshall<ll> fw(2);
		fw.addedge(0, 0, 1);  // Self-loop (should be ignored as dist[0][0] = 0)
		fw.addedge(0, 1, 5);
		
		assert(fw.run());
		assert(fw.get_dist(0, 0) == 0);  // Self-loop doesn't change distance
		assert(fw.get_dist(0, 1) == 5);
	}

	// Test 11: Zero weight edges
	{
		FloydWarshall<ll> fw(4);
		fw.addedge(0, 1, 0);
		fw.addedge(1, 2, 0);
		fw.addedge(2, 3, 5);
		
		assert(fw.run());
		assert(fw.get_dist(0, 3) == 5);
		assert(fw.get_dist(0, 1) == 0);
		assert(fw.get_dist(1, 2) == 0);
	}

	// Test 12: Multiple edges between same nodes
	{
		FloydWarshall<ll> fw(2);
		fw.addedge(0, 1, 10);
		fw.addedge(0, 1, 5);   // Should take minimum
		
		assert(fw.run());
		assert(fw.get_dist(0, 1) == 5);
	}

	// Test 13: Directed vs undirected
	{
		// Directed
		FloydWarshall<ll> fw_dir(3);
		fw_dir.addedge(0, 1, 1, true);
		fw_dir.addedge(1, 2, 1, true);
		
		assert(fw_dir.run());
		assert(fw_dir.get_dist(0, 2) == 2);
		assert(fw_dir.get_dist(2, 0) == numeric_limits<ll>::max());
		
		// Undirected
		FloydWarshall<ll> fw_undir(3);
		fw_undir.addedge(0, 1, 1, false);
		fw_undir.addedge(1, 2, 1, false);
		
		assert(fw_undir.run());
		assert(fw_undir.get_dist(0, 2) == 2);
		assert(fw_undir.get_dist(2, 0) == 2);  // Can go backwards
	}

	// Test 14: All-pairs correctness verification
	{
		int n = 5;
		FloydWarshall<ll> fw(n);
		
		// Build adjacency list for naive verification
		vector<vector<pair<int, ll>>> g(n);
		
		fw.addedge(0, 1, 2);
		g[0].emplace_back(1, 2);
		g[1].emplace_back(0, 2);
		
		fw.addedge(1, 2, 3);
		g[1].emplace_back(2, 3);
		g[2].emplace_back(1, 3);
		
		fw.addedge(2, 3, 1);
		g[2].emplace_back(3, 1);
		g[3].emplace_back(2, 1);
		
		fw.addedge(3, 4, 4);
		g[3].emplace_back(4, 4);
		g[4].emplace_back(3, 4);
		
		fw.addedge(0, 4, 15);  // Direct path (longer)
		g[0].emplace_back(4, 15);
		g[4].emplace_back(0, 15);
		
		assert(fw.run());
		auto naive_dist = naive_apsp(g);
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				assert(fw.get_dist(i, j) == naive_dist[i][j]);
			}
		}
	}

	// Test 15: Fuzzy testing with small random graphs
	{
		mt19937 rng(42);
		
		for (int test = 0; test < 30; test++) {
			int n = 2 + rng() % 10;
			FloydWarshall<ll> fw(n);
			vector<vector<pair<int, ll>>> g(n);
			
			// Generate random edges
			int num_edges = n + rng() % (n * 2);
			for (int i = 0; i < num_edges; i++) {
				int a = rng() % n;
				int b = rng() % n;
				if (a != b) {
					ll w = 1 + rng() % 20;
					fw.addedge(a, b, w);
					g[a].emplace_back(b, w);
					g[b].emplace_back(a, w);
				}
			}
			
			fw.run();
			auto naive_dist = naive_apsp(g);
			
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					assert(fw.get_dist(i, j) == naive_dist[i][j]);
				}
			}
		}
	}

	// Test 16: Path reconstruction verification
	{
		FloydWarshall<ll> fw(5);
		fw.addedge(0, 1, 2);
		fw.addedge(1, 2, 3);
		fw.addedge(2, 3, 1);
		fw.addedge(3, 4, 4);
		fw.addedge(0, 4, 100);  // Direct path is longer
		
		fw.run();
		auto path = fw.get_path(0, 4);
		
		// Verify path is valid
		assert(!path.empty());
		assert(path[0] == 0);
		assert(path.back() == 4);
		
		// Verify path matches distance
		ll path_dist = 0;
		for (size_t i = 0; i < path.size() - 1; i++) {
			int a = path[i];
			int b = path[i + 1];
			// Check that edges exist (we can't verify exact weights here)
			assert(fw.get_dist(a, b) != numeric_limits<ll>::max());
			path_dist += fw.get_dist(a, b);
		}
		// Path distance should match total distance
		assert(path_dist == fw.get_dist(0, 4));
	}

	// Test 17: Disconnected components
	{
		FloydWarshall<ll> fw(6);
		fw.addedge(0, 1, 1);
		fw.addedge(1, 2, 1);
		fw.addedge(3, 4, 1);
		fw.addedge(4, 5, 1);
		
		assert(fw.run());
		assert(fw.get_dist(0, 2) == 2);
		assert(fw.get_dist(3, 5) == 2);
		assert(fw.get_dist(0, 3) == numeric_limits<ll>::max());
		assert(fw.get_dist(2, 4) == numeric_limits<ll>::max());
	}

	// Test 18: Different weight types
	{
		// Integer weights
		FloydWarshall<int> fw_int(3);
		fw_int.addedge(0, 1, 5);
		fw_int.addedge(1, 2, 3);
		assert(fw_int.run());
		assert(fw_int.get_dist(0, 2) == 8);
		
		// Long long weights
		FloydWarshall<ll> fw_ll(3);
		fw_ll.addedge(0, 1, 1000000000LL);
		fw_ll.addedge(1, 2, 1000000000LL);
		assert(fw_ll.run());
		assert(fw_ll.get_dist(0, 2) == 2000000000LL);
	}

	cout << "All Floyd-Warshall tests passed!" << endl;
	return 0;
}


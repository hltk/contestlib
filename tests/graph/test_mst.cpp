#include "../../graph/mst.cpp"
#include <cassert>
#include <iostream>
#include <random>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
using ll = long long;

// Prim's algorithm for MST verification (different approach than Kruskal)
// Builds MST by growing from a starting vertex, always adding minimum edge
// that connects a vertex in MST to one outside
template<typename T>
pair<T, vector<pair<int, int>>> prim_mst(int n, const vector<tuple<int, int, T>>& edges_vec) {
	if (n == 0) return {0, {}};
	if (n == 1) return {0, {}};

	// Build adjacency list
	vector<vector<pair<int, T>>> g(n);
	for (const auto& [u, v, w] : edges_vec) {
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}

	// Prim's algorithm
	vector<bool> in_mst(n, false);
	priority_queue<pair<T, pair<int, int>>, vector<pair<T, pair<int, int>>>, greater<>> pq;
	
	T total_weight = 0;
	vector<pair<int, int>> mst_edges;
	
	// Process all components (handles disconnected graphs)
	for (int start = 0; start < n; start++) {
		if (in_mst[start]) continue;

		// Start new component
		in_mst[start] = true;
		for (auto [v, w] : g[start]) {
			if (!in_mst[v]) {
				pq.push({w, {start, v}});
			}
		}

		// Grow MST for this component
		while (!pq.empty()) {
			auto [w, edge] = pq.top();
			auto [u, v] = edge;
			pq.pop();

			if (in_mst[u] && in_mst[v]) continue;

			// One of u or v must be outside MST
			int outside = in_mst[u] ? v : u;
			in_mst[outside] = true;
			total_weight += w;
			mst_edges.push_back({u, v});

			// Add edges from the newly added vertex
			for (auto [to, weight] : g[outside]) {
				if (!in_mst[to]) {
					pq.push({weight, {outside, to}});
				}
			}
		}
	}

	return {total_weight, mst_edges};
}

int main() {
	// Test 1: Single node
	{
		MST<ll> mst(1);
		auto [weight, edges] = mst.run();
		assert(weight == 0);
		assert(edges.empty());
	}

	// Test 2: Two nodes - connected
	{
		MST<ll> mst(2);
		mst.addedge(0, 1, 5);
		auto [weight, edges] = mst.run();
		assert(weight == 5);
		assert(edges.size() == 1);
		assert(edges[0].u == 0 && edges[0].v == 1 && edges[0].w == 5);
	}

	// Test 3: Two nodes - disconnected (multiple edges)
	{
		MST<ll> mst(2);
		mst.addedge(0, 1, 10);
		mst.addedge(0, 1, 5);  // Duplicate edge with different weight
		auto [weight, edges] = mst.run();
		assert(weight == 5);  // Should pick minimum weight edge
		assert(edges.size() == 1);
	}

	// Test 4: Triangle - verify correct MST
	{
		MST<ll> mst(3);
		mst.addedge(0, 1, 1);
		mst.addedge(1, 2, 2);
		mst.addedge(0, 2, 5);  // This edge should not be in MST
		
		auto [weight, edges] = mst.run();
		assert(weight == 3);  // 1 + 2
		assert(edges.size() == 2);
		
		// Check that heavy edge is not included
		bool has_heavy = false;
		for (const auto& e : edges) {
			if (e.w == 5) has_heavy = true;
		}
		assert(!has_heavy);
	}

	// Test 5: Simple path graph
	{
		MST<ll> mst(4);
		mst.addedge(0, 1, 1);
		mst.addedge(1, 2, 2);
		mst.addedge(2, 3, 3);
		
		auto [weight, edges] = mst.run();
		assert(weight == 6);  // 1 + 2 + 3
		assert(edges.size() == 3);
	}

	// Test 6: Multiple paths - verify minimum is chosen
	{
		MST<ll> mst(4);
		mst.addedge(0, 1, 10);
		mst.addedge(1, 3, 10);  // Path 0->1->3 = 20
		mst.addedge(0, 2, 5);
		mst.addedge(2, 3, 5);   // Path 0->2->3 = 10 (should be chosen)
		
		auto [weight, edges] = mst.run();
		// MST should be: 0-2 (5), 2-3 (5), and one of 0-1 or 1-3 (10) to connect node 1
		// Total weight = 5 + 5 + 10 = 20
		assert(weight == 20);
		assert(edges.size() == 3);
	}

	// Test 7: Complete graph K4
	{
		MST<ll> mst(4);
		mst.addedge(0, 1, 1);
		mst.addedge(0, 2, 2);
		mst.addedge(0, 3, 3);
		mst.addedge(1, 2, 4);
		mst.addedge(1, 3, 5);
		mst.addedge(2, 3, 6);
		
		auto [weight, edges] = mst.run();
		// MST should use edges with weights 1, 2, 3 = 6
		assert(weight == 6);
		assert(edges.size() == 3);
	}

	// Test 8: Disconnected components (spanning forest)
	{
		MST<ll> mst(6);
		mst.addedge(0, 1, 1);
		mst.addedge(1, 2, 1);
		mst.addedge(3, 4, 1);
		mst.addedge(4, 5, 1);
		
		auto [weight, edges] = mst.run();
		// Should get spanning forest with weight 4 (two components)
		assert(weight == 4);
		assert(edges.size() == 4);
	}

	// Test 9: Zero weight edges
	{
		MST<ll> mst(3);
		mst.addedge(0, 1, 0);
		mst.addedge(1, 2, 5);
		
		auto [weight, edges] = mst.run();
		assert(weight == 5);
		assert(edges.size() == 2);
	}

	// Test 10: All same weights
	{
		MST<ll> mst(4);
		mst.addedge(0, 1, 5);
		mst.addedge(1, 2, 5);
		mst.addedge(2, 3, 5);
		
		auto [weight, edges] = mst.run();
		assert(weight == 15);  // 5 * 3
		assert(edges.size() == 3);
	}

	// Test 11: Large weights
	{
		MST<ll> mst(3);
		mst.addedge(0, 1, 1000000000LL);
		mst.addedge(1, 2, 1000000000LL);
		
		auto [weight, edges] = mst.run();
		assert(weight == 2000000000LL);
	}

	// Test 12: Different weight types
	{
		// Integer weights
		MST<int> mst_int(3);
		mst_int.addedge(0, 1, 5);
		mst_int.addedge(1, 2, 3);
		auto [w_int, _] = mst_int.run();
		assert(w_int == 8);

		// Long long weights
		MST<ll> mst_ll(3);
		mst_ll.addedge(0, 1, 1000000000LL);
		mst_ll.addedge(1, 2, 1000000000LL);
		auto [w_ll, __] = mst_ll.run();
		assert(w_ll == 2000000000LL);
	}

	// Test 13: Get weight only
	{
		MST<ll> mst(3);
		mst.addedge(0, 1, 5);
		mst.addedge(1, 2, 3);
		assert(mst.get_weight() == 8);
	}

	// Test 14: Get edges only
	{
		MST<ll> mst(3);
		mst.addedge(0, 1, 5);
		mst.addedge(1, 2, 3);
		auto edges = mst.get_edges();
		assert(edges.size() == 2);
	}

	// Test 15: Fuzzy testing with random graphs
	{
		mt19937 rng(42);
		
		for (int test = 0; test < 50; test++) {
			int n = 2 + rng() % 15;
			MST<ll> mst(n);
			
			vector<tuple<int, int, ll>> edges_vec;
			
			// Generate random edges
			int num_edges = max(1, n - 1) + rng() % (n * 2);
			for (int i = 0; i < num_edges; i++) {
				int a = rng() % n;
				int b = rng() % n;
				if (a != b) {
					ll w = 1 + rng() % 100;
					mst.addedge(a, b, w);
					edges_vec.push_back({a, b, w});
				}
			}
			
			auto [weight, edges] = mst.run();
			auto [prim_weight, prim_edges] = prim_mst(n, edges_vec);
			
			assert(weight == prim_weight);
			assert(edges.size() == prim_edges.size());
		}
	}

	// Test 16: Star graph
	{
		int n = 5;
		MST<ll> mst(n);
		for (int i = 1; i < n; i++) {
			mst.addedge(0, i, i);
		}
		
		auto [weight, edges] = mst.run();
		assert(weight == 1 + 2 + 3 + 4);
		assert(int(edges.size()) == n - 1);
	}

	// Test 17: Cycle - verify one edge is excluded
	{
		MST<ll> mst(4);
		mst.addedge(0, 1, 1);
		mst.addedge(1, 2, 2);
		mst.addedge(2, 3, 3);
		mst.addedge(3, 0, 4);  // This forms a cycle, heaviest edge should be excluded
		
		auto [weight, edges] = mst.run();
		// MST should exclude edge 3-0 (weight 4)
		assert(weight == 1 + 2 + 3);  // = 6
		assert(edges.size() == 3);
	}

	// Test 18: Single edge graph
	{
		MST<ll> mst(2);
		mst.addedge(0, 1, 42);
		auto weight = mst.get_weight();
		assert(weight == 42);
	}

	// Test 19: Multiple edges between same nodes
	{
		MST<ll> mst(2);
		mst.addedge(0, 1, 10);
		mst.addedge(0, 1, 5);   // Duplicate with lower weight
		mst.addedge(0, 1, 15);  // Duplicate with higher weight
		
		auto [weight, edges] = mst.run();
		// Should pick the minimum weight edge (5)
		assert(weight == 5);
		assert(edges.size() == 1);
	}

	// Test 20: Self-loops (should be ignored by DSU)
	{
		MST<ll> mst(3);
		mst.addedge(0, 1, 5);
		mst.addedge(1, 2, 3);
		// Self-loops won't be added by addedge, but if they were, DSU would ignore them
		auto [weight, edges] = mst.run();
		assert(weight == 8);
		assert(edges.size() == 2);
	}

	cout << "All MST tests passed!" << endl;
	return 0;
}


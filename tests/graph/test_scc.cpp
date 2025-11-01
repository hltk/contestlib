#include "../../graph/scc.cpp"
#include <cassert>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

// Helper function to check if two components have the same vertices
bool same_component(const vector<int>& c1, const vector<int>& c2) {
	if (c1.size() != c2.size()) return false;
	vector<int> s1(c1.begin(), c1.end());
	vector<int> s2(c2.begin(), c2.end());
	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());
	return s1 == s2;
}

int main() {
	// Test 1: Single node
	{
		SCC scc(1);
		auto comps = scc.run();
		assert(comps.size() == 1);
		assert(comps[0].size() == 1);
		assert(comps[0][0] == 0);
		assert(scc.comps.size() == 1);
		assert(scc.comp[0] == 0);
	}

	// Test 2: Empty graph (no edges)
	{
		SCC scc(3);
		auto comps = scc.run();
		assert(comps.size() == 3);
		assert(comps[0].size() == 1);
		assert(comps[1].size() == 1);
		assert(comps[2].size() == 1);
	}

	// Test 3: Simple cycle (all nodes in one SCC)
	{
		SCC scc(3);
		scc.addedge(0, 1);
		scc.addedge(1, 2);
		scc.addedge(2, 0);
		
		auto comps = scc.run();
		assert(comps.size() == 1);
		assert(comps[0].size() == 3);
		sort(comps[0].begin(), comps[0].end());
		assert(comps[0][0] == 0);
		assert(comps[0][1] == 1);
		assert(comps[0][2] == 2);
		assert(scc.comp[0] == scc.comp[1]);
		assert(scc.comp[1] == scc.comp[2]);
	}

	// Test 4: Two-node cycle
	{
		SCC scc(2);
		scc.addedge(0, 1);
		scc.addedge(1, 0);
		
		auto comps = scc.run();
		assert(comps.size() == 1);
		assert(comps[0].size() == 2);
	}

	// Test 5: DAG (each node is its own SCC)
	{
		SCC scc(4);
		scc.addedge(0, 1);
		scc.addedge(1, 2);
		scc.addedge(0, 3);
		
		auto comps = scc.run();
		assert(comps.size() == 4);
		for (const auto& comp : comps) {
			assert(comp.size() == 1);
		}
		assert(scc.comp[0] != scc.comp[1]);
		assert(scc.comp[1] != scc.comp[2]);
	}

	// Test 6: Multiple SCCs
	{
		SCC scc(6);
		// Component 1: 0 <-> 1
		scc.addedge(0, 1);
		scc.addedge(1, 0);
		// Component 2: 2 <-> 3
		scc.addedge(2, 3);
		scc.addedge(3, 2);
		// Component 3: 4
		// Component 4: 5
		// Edge from component 1 to component 2
		scc.addedge(0, 2);
		
		auto comps = scc.run();
		assert(comps.size() == 4);
		
		// Verify all vertices are in exactly one component
		vector<bool> found(6, false);
		for (const auto& comp : comps) {
			for (int v : comp) {
				assert(!found[v]);
				found[v] = true;
			}
		}
		for (bool f : found) assert(f);
		
		// Verify vertices in same cycle are together
		assert(scc.comp[0] == scc.comp[1]);
		assert(scc.comp[2] == scc.comp[3]);
		assert(scc.comp[0] != scc.comp[2]);
		assert(scc.comp[4] != scc.comp[5]);
	}

	// Test 7: Self-loop
	{
		SCC scc(2);
		scc.addedge(0, 0);  // Self-loop
		scc.addedge(0, 1);
		
		auto comps = scc.run();
		// Self-loop makes 0 its own SCC
		assert(comps.size() == 2);
		bool found_zero = false;
		for (const auto& comp : comps) {
			if (comp.size() == 1 && comp[0] == 0) {
				found_zero = true;
			}
		}
		assert(found_zero);
	}

	// Test 8: Complex graph with nested cycles
	{
		SCC scc(5);
		// Cycle: 0 -> 1 -> 2 -> 0
		scc.addedge(0, 1);
		scc.addedge(1, 2);
		scc.addedge(2, 0);
		// Chain: 3 -> 4
		scc.addedge(3, 4);
		// Edge from cycle to chain
		scc.addedge(0, 3);
		
		auto comps = scc.run();
		// Should have 3 components: {0,1,2}, {3}, {4}
		assert(comps.size() == 3);
		
		// Find the large component (cycle)
		int cycle_comp = -1;
		for (size_t i = 0; i < comps.size(); i++) {
			if (comps[i].size() == 3) {
				cycle_comp = i;
				sort(comps[i].begin(), comps[i].end());
				assert(comps[i][0] == 0);
				assert(comps[i][1] == 1);
				assert(comps[i][2] == 2);
			}
		}
		assert(cycle_comp != -1);
		assert(scc.comp[0] == scc.comp[1]);
		assert(scc.comp[1] == scc.comp[2]);
		assert(scc.comp[0] != scc.comp[3]);
		assert(scc.comp[3] != scc.comp[4]);
	}

	// Test 9: Two separate cycles
	{
		SCC scc(6);
		// Cycle 1: 0 <-> 1
		scc.addedge(0, 1);
		scc.addedge(1, 0);
		// Cycle 2: 2 <-> 3 <-> 4 <-> 2
		scc.addedge(2, 3);
		scc.addedge(3, 4);
		scc.addedge(4, 2);
		// Isolated node: 5
		
		auto comps = scc.run();
		assert(comps.size() == 3);
		
		set<int> comp_sizes;
		for (const auto& comp : comps) {
			comp_sizes.insert(comp.size());
		}
		assert(comp_sizes.count(1) == 1);  // One isolated node
		assert(comp_sizes.count(2) == 1);  // One 2-cycle
		assert(comp_sizes.count(3) == 1);  // One 3-cycle
	}

	// Test 10: Get component method
	{
		SCC scc(4);
		scc.addedge(0, 1);
		scc.addedge(1, 0);
		scc.addedge(2, 3);
		
		auto comps = scc.run();
		auto comp1 = scc.comps[scc.comp[0]];
		auto comp2 = scc.comps[scc.comp[1]];
		auto comp3 = scc.comps[scc.comp[2]];
		
		assert(same_component(comp1, comp2));
		assert(!same_component(comp1, comp3));
		assert(comp1.size() == 2);
		assert(comp3.size() == 1);
	}

	// Test 11: Large cycle
	{
		int n = 10;
		SCC scc(n);
		for (int i = 0; i < n; i++) {
			scc.addedge(i, (i + 1) % n);
		}
		
		auto comps = scc.run();
		assert(comps.size() == 1);
		assert(comps[0].size() == (size_t)n);
	}

	// Test 12: Linear chain (DAG, each node separate)
	{
		int n = 5;
		SCC scc(n);
		for (int i = 0; i < n - 1; i++) {
			scc.addedge(i, i + 1);
		}
		
		auto comps = scc.run();
		assert(comps.size() == (size_t)n);
		for (const auto& comp : comps) {
			assert(comp.size() == 1);
		}
	}

	// Test 13: Multiple calls to run()
	{
		SCC scc(3);
		scc.addedge(0, 1);
		scc.addedge(1, 0);
		
		auto comps1 = scc.run();
		auto comps2 = scc.run();
		
		assert(comps1.size() == comps2.size());
		assert(comps1[0].size() == comps2[0].size());
	}

	// Test 14: Disconnected cycles
	{
		SCC scc(6);
		// Component 1: 0 <-> 1
		scc.addedge(0, 1);
		scc.addedge(1, 0);
		// Component 2: 2 <-> 3
		scc.addedge(2, 3);
		scc.addedge(3, 2);
		// Component 3: 4 <-> 5
		scc.addedge(4, 5);
		scc.addedge(5, 4);
		
		auto comps = scc.run();
		assert(comps.size() == 3);
		for (const auto& comp : comps) {
			assert(comp.size() == 2);
		}
	}

	// Test 15: Verify all vertices present
	{
		SCC scc(8);
		scc.addedge(0, 1);
		scc.addedge(1, 0);
		scc.addedge(2, 3);
		scc.addedge(4, 5);
		scc.addedge(5, 4);
		
		auto comps = scc.run();
		set<int> all_vertices;
		for (const auto& comp : comps) {
			for (int v : comp) {
				all_vertices.insert(v);
			}
		}
		assert(all_vertices.size() == 8);
		for (int i = 0; i < 8; i++) {
			assert(all_vertices.count(i) == 1);
		}
	}

	// Test 16: Complex nested structure
	{
		SCC scc(7);
		// Main cycle: 0 -> 1 -> 2 -> 0
		scc.addedge(0, 1);
		scc.addedge(1, 2);
		scc.addedge(2, 0);
		// Attached cycle: 3 -> 4 -> 3
		scc.addedge(3, 4);
		scc.addedge(4, 3);
		// Edge from main to attached
		scc.addedge(1, 3);
		// Isolated: 5, 6
		
		auto comps = scc.run();
		// Should have 3 components: {0,1,2}, {3,4}, {5}, {6}
		assert(comps.size() == 4);
		
		int large_comp_count = 0;
		for (const auto& comp : comps) {
			if (comp.size() >= 2) {
				large_comp_count++;
			}
		}
		assert(large_comp_count == 2);  // Two cycles
	}

	// Test 17: Verify topological order of components
	{
		SCC scc(5);
		// Component 1: 0 <-> 1
		scc.addedge(0, 1);
		scc.addedge(1, 0);
		// Component 2: 2 <-> 3
		scc.addedge(2, 3);
		scc.addedge(3, 2);
		// Edge from component 1 to component 2
		scc.addedge(0, 2);
		
		auto comps = scc.run();
		// Component 1 should come before component 2 in topological order
		int comp1_id = scc.comp[0];
		int comp2_id = scc.comp[2];
		assert(comp1_id < comp2_id);  // In topological order
	}

	// Test 18: Single large strongly connected component
	{
		int n = 10;
		SCC scc(n);
		// Create a complete directed cycle
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i != j) {
					scc.addedge(i, j);
				}
			}
		}
		
		auto comps = scc.run();
		assert(comps.size() == 1);
		assert(comps[0].size() == (size_t)n);
	}

	cout << "All SCC tests passed!" << endl;
	return 0;
}


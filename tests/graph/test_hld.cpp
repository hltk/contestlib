#include "../../graph/hld.cpp"
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	// Test 1: Single node
	{
		graph g(1);
		HLD hld(g);
		
		assert(hld.pos(0) == 0);
		auto [l, r] = hld.subtree(0);
		assert(l == 0 && r == 1);  // Half-open interval [0, 1)
	}

	// Test 2: Two nodes (parent-child)
	{
		// 0 -- 1
		graph g(2);
		g[0].push_back(1);
		
		HLD hld(g);
		
		// Both nodes should be positioned
		assert(hld.pos(0) == 0);
		assert(hld.pos(1) == 1);
		
		// Subtree of 0 should contain both nodes
		auto [l0, r0] = hld.subtree(0);
		assert(l0 == 0 && r0 == 2);
		
		// Subtree of 1 should contain only itself
		auto [l1, r1] = hld.subtree(1);
		assert(l1 == 1 && r1 == 2);
		
		// LCA test
		assert(hld.lca(0, 1) == 0);
		assert(hld.lca(1, 0) == 0);
	}

	// Test 3: Linear chain
	{
		// 0 -- 1 -- 2 -- 3 -- 4
		graph g(5);
		g[0].push_back(1);
		g[1].push_back(2);
		g[2].push_back(3);
		g[3].push_back(4);
		
		HLD hld(g);
		
		// Positions should be assigned
		for (int i = 0; i < 5; ++i) {
			assert(hld.pos(i) >= 0 && hld.pos(i) < 5);
		}
		
		// LCA tests
		assert(hld.lca(0, 0) == 0);
		assert(hld.lca(1, 2) == 1);
		assert(hld.lca(0, 4) == 0);
		assert(hld.lca(2, 4) == 2);
		assert(hld.lca(3, 4) == 3);
		
		// Path query test
		auto path = hld.query(0, 4);
		assert(!path.empty());
	}

	// Test 4: Star graph
	{
		// Center: 0, leaves: 1, 2, 3, 4
		graph g(5);
		g[0].push_back(1);
		g[0].push_back(2);
		g[0].push_back(3);
		g[0].push_back(4);
		
		HLD hld(g);
		
		// All leaves have LCA at root
		assert(hld.lca(1, 2) == 0);
		assert(hld.lca(1, 3) == 0);
		assert(hld.lca(2, 4) == 0);
		assert(hld.lca(3, 4) == 0);
		
		// Node with itself
		assert(hld.lca(0, 0) == 0);
		assert(hld.lca(1, 1) == 1);
		
		// Root with any node
		assert(hld.lca(0, 1) == 0);
		assert(hld.lca(0, 4) == 0);
	}

	// Test 5: Binary tree
	{
		//       0
		//      / \.
		//     1   2
		//    / \ / \.
		//   3  4 5  6
		graph g(7);
		g[0].push_back(1);
		g[0].push_back(2);
		g[1].push_back(3);
		g[1].push_back(4);
		g[2].push_back(5);
		g[2].push_back(6);
		
		HLD hld(g);
		
		// LCA tests
		assert(hld.lca(0, 0) == 0);
		assert(hld.lca(3, 4) == 1);
		assert(hld.lca(5, 6) == 2);
		assert(hld.lca(3, 5) == 0);
		assert(hld.lca(4, 6) == 0);
		assert(hld.lca(1, 2) == 0);
		assert(hld.lca(3, 1) == 1);
		
		// Subtree tests
		auto [l0, r0] = hld.subtree(0);
		assert(r0 - l0 == 7);  // Root contains all nodes
		
		auto [l1, r1] = hld.subtree(1);
		assert(r1 - l1 == 3);  // Node 1 has 3 nodes in subtree (1, 3, 4)
		
		auto [l3, r3] = hld.subtree(3);
		assert(r3 - l3 == 1);  // Leaf has only itself
	}

	// Test 6: Deep tree (path)
	{
		// 0 -- 1 -- 2 -- 3 -- 4 -- 5 -- 6 -- 7 -- 8 -- 9
		graph g(10);
		for (int i = 0; i < 9; ++i) {
			g[i].push_back(i + 1);
		}
		
		HLD hld(g);
		
		// LCA tests for path
		assert(hld.lca(0, 9) == 0);
		assert(hld.lca(5, 9) == 5);
		assert(hld.lca(2, 7) == 2);
		assert(hld.lca(4, 4) == 4);
		
		// Query path
		auto path = hld.query(3, 7);
		assert(!path.empty());
		
		// Subtree size checks
		auto [l0, r0] = hld.subtree(0);
		assert(r0 - l0 == 10);  // Root has all nodes
		
		auto [l5, r5] = hld.subtree(5);
		assert(r5 - l5 == 5);  // Node 5 has 5 nodes in subtree (5-9)
	}

	// Test 7: Y-shaped tree
	{
		//   0
		//   |
		//   1
		//  / \.
		// 2   3
		graph g(4);
		g[0].push_back(1);
		g[1].push_back(2);
		g[1].push_back(3);
		
		HLD hld(g);
		
		assert(hld.lca(0, 1) == 0);
		assert(hld.lca(0, 2) == 0);
		assert(hld.lca(1, 2) == 1);
		assert(hld.lca(2, 3) == 1);
		assert(hld.lca(0, 3) == 0);
	}

	// Test 8: Query path symmetry
	{
		//       0
		//      / \.
		//     1   2
		//    /     \.
		//   3       4
		graph g(5);
		g[0].push_back(1);
		g[0].push_back(2);
		g[1].push_back(3);
		g[2].push_back(4);
		
		HLD hld(g);
		
		// Query should be symmetric
		auto path1 = hld.query(3, 4);
		auto path2 = hld.query(4, 3);
		
		// Both should cover the same path (may be in different order)
		assert(!path1.empty());
		assert(!path2.empty());
		
		// LCA should be symmetric
		assert(hld.lca(3, 4) == hld.lca(4, 3));
		assert(hld.lca(3, 4) == 0);
	}

	// Test 9: Complex tree structure
	{
		//        0
		//       /|\.
		//      1 2 3
		//     /|   |\.
		//    4 5   6 7
		graph g(8);
		g[0].push_back(1);
		g[0].push_back(2);
		g[0].push_back(3);
		g[1].push_back(4);
		g[1].push_back(5);
		g[3].push_back(6);
		g[3].push_back(7);
		
		HLD hld(g);
		
		// Various LCA tests
		assert(hld.lca(4, 5) == 1);
		assert(hld.lca(6, 7) == 3);
		assert(hld.lca(4, 6) == 0);
		assert(hld.lca(5, 7) == 0);
		assert(hld.lca(1, 3) == 0);
		assert(hld.lca(2, 0) == 0);
		
		// Subtree sizes
		auto [l0, r0] = hld.subtree(0);
		assert(r0 - l0 == 8);
		
		auto [l1, r1] = hld.subtree(1);
		assert(r1 - l1 == 3);  // 1, 4, 5
		
		auto [l2, r2] = hld.subtree(2);
		assert(r2 - l2 == 1);  // Just 2
	}

	// Test 10: All positions unique
	{
		//       0
		//      / \.
		//     1   2
		//    / \ / \.
		//   3  4 5  6
		graph g(7);
		g[0].push_back(1);
		g[0].push_back(2);
		g[1].push_back(3);
		g[1].push_back(4);
		g[2].push_back(5);
		g[2].push_back(6);
		
		HLD hld(g);
		
		// All positions should be unique and in range [0, n)
		vector<bool> used(7, false);
		for (int i = 0; i < 7; ++i) {
			int pos = hld.pos(i);
			assert(pos >= 0 && pos < 7);
			assert(!used[pos]);
			used[pos] = true;
		}
	}

	cout << "All HLD tests passed!" << endl;
	return 0;
}

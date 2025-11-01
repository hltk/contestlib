#include "../../graph/centroid.cpp"
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

// Helper function to verify tree structure
bool verify_tree(const graph& tree, int n) {
	int edge_count = 0;
	for (const auto& adj : tree) {
		edge_count += adj.size();
	}
	return edge_count == n - 1;  // Tree has n-1 edges
}

int main() {
	// Test 1: Single node
	{
		graph g(1);
		auto [decomp, root] = centroid::decomp(g);
		
		assert(root == 0);
		assert(decomp.size() == 1);
		assert(decomp[0].empty());
	}

	// Test 2: Two nodes (simple path)
	{
		// 0 -- 1
		graph g(2);
		g[0].push_back(1);
		g[1].push_back(0);
		
		auto [decomp, root] = centroid::decomp(g);
		
		assert(decomp.size() == 2);
		// One node should be the root with no parent
		// The other should be a child
		int children_count = 0;
		for (const auto& adj : decomp) {
			children_count += adj.size();
		}
		assert(children_count == 1);  // Only one parent-child relationship
	}

	// Test 3: Linear chain (path graph)
	{
		// 0 -- 1 -- 2 -- 3 -- 4
		graph g(5);
		for (int i = 0; i < 4; ++i) {
			g[i].push_back(i + 1);
			g[i + 1].push_back(i);
		}
		
		auto [decomp, root] = centroid::decomp(g);
		
		assert(decomp.size() == 5);
		// Centroid should be node 2 (middle)
		assert(root == 2);
		verify_tree(decomp, 5);
	}

	// Test 4: Star graph (one center, all others connected to it)
	{
		// Center: 0, leaves: 1, 2, 3, 4
		graph g(5);
		for (int i = 1; i < 5; ++i) {
			g[0].push_back(i);
			g[i].push_back(0);
		}
		
		auto [decomp, root] = centroid::decomp(g);
		
		assert(decomp.size() == 5);
		// Root should be node 0 (the center)
		assert(root == 0);
		// Node 0 should have all others as children in decomposition
		assert(decomp[0].size() == 4);
	}

	// Test 5: Balanced binary tree
	{
		//       0
		//      / \.
		//     1   2
		//    / \ / \.
		//   3  4 5  6
		graph g(7);
		g[0].push_back(1); g[1].push_back(0);
		g[0].push_back(2); g[2].push_back(0);
		g[1].push_back(3); g[3].push_back(1);
		g[1].push_back(4); g[4].push_back(1);
		g[2].push_back(5); g[5].push_back(2);
		g[2].push_back(6); g[6].push_back(2);
		
		auto [decomp, root] = centroid::decomp(g);
		
		assert(decomp.size() == 7);
		assert(root == 0);  // Root should be centroid (node 0)
		verify_tree(decomp, 7);
	}

	// Test 6: Three-node path
	{
		// 0 -- 1 -- 2
		graph g(3);
		g[0].push_back(1); g[1].push_back(0);
		g[1].push_back(2); g[2].push_back(1);
		
		auto [decomp, root] = centroid::decomp(g);
		
		assert(decomp.size() == 3);
		assert(root == 1);  // Middle node should be centroid
		assert(decomp[1].size() == 2);  // Node 1 has two children
	}

	// Test 7: Unbalanced tree
	{
		//     0
		//    /|\.
		//   1 2 3
		//  /
		// 4
		graph g(5);
		g[0].push_back(1); g[1].push_back(0);
		g[0].push_back(2); g[2].push_back(0);
		g[0].push_back(3); g[3].push_back(0);
		g[1].push_back(4); g[4].push_back(1);
		
		auto [decomp, root] = centroid::decomp(g);
		
		assert(decomp.size() == 5);
		assert(root == 0);  // Node 0 should be the centroid
		verify_tree(decomp, 5);
	}

	// Test 8: Larger path
	{
		// 0 -- 1 -- 2 -- 3 -- 4 -- 5 -- 6 -- 7 -- 8 -- 9
		graph g(10);
		for (int i = 0; i < 9; ++i) {
			g[i].push_back(i + 1);
			g[i + 1].push_back(i);
		}
		
		auto [decomp, root] = centroid::decomp(g);
		
		assert(decomp.size() == 10);
		// Centroid should be around the middle (4 or 5)
		assert(root == 4 || root == 5);
		verify_tree(decomp, 10);
	}

	// Test 9: Complete binary tree of height 3
	{
		//          0
		//        /   \.
		//       1     2
		//      / \   / \.
		//     3   4 5   6
		//    / \.
		//   7   8
		graph g(9);
		g[0].push_back(1); g[1].push_back(0);
		g[0].push_back(2); g[2].push_back(0);
		g[1].push_back(3); g[3].push_back(1);
		g[1].push_back(4); g[4].push_back(1);
		g[2].push_back(5); g[5].push_back(2);
		g[2].push_back(6); g[6].push_back(2);
		g[3].push_back(7); g[7].push_back(3);
		g[3].push_back(8); g[8].push_back(3);
		
		auto [decomp, root] = centroid::decomp(g);
		
		assert(decomp.size() == 9);
		verify_tree(decomp, 9);
	}

	// Test 10: Y-shaped tree
	{
		//   0
		//   |
		//   1
		//  / \.
		// 2   3
		graph g(4);
		g[0].push_back(1); g[1].push_back(0);
		g[1].push_back(2); g[2].push_back(1);
		g[1].push_back(3); g[3].push_back(1);
		
		auto [decomp, root] = centroid::decomp(g);
		
		assert(decomp.size() == 4);
		assert(root == 1);  // Node 1 is the centroid
		verify_tree(decomp, 4);
	}

	cout << "All centroid decomposition tests passed!" << endl;
	return 0;
}

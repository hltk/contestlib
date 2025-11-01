#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// Disable the main function in lca.cpp
#define main main_disabled
#include "../../graph/lca.cpp"
#undef main

int main() {
	// Test 1: Simple path
	{
		//     0
		//     |
		//     1
		//     |
		//     2
		//     |
		//     3
		vector<vector<int>> g(4);
		g[0].push_back(1);
		g[1].push_back(0);
		g[1].push_back(2);
		g[2].push_back(1);
		g[2].push_back(3);
		g[3].push_back(2);
		
		LCA lca(g);
		
		assert(lca.query(0, 0) == 0);
		assert(lca.query(1, 2) == 1);
		assert(lca.query(2, 3) == 2);
		assert(lca.query(1, 3) == 1);
		assert(lca.query(0, 3) == 0);
	}

	// Test 2: Binary tree
	{
		//       0
		//      / \
		//     1   2
		//    / \
		//   3   4
		vector<vector<int>> g(5);
		g[0].push_back(1);
		g[0].push_back(2);
		g[1].push_back(0);
		g[1].push_back(3);
		g[1].push_back(4);
		g[2].push_back(0);
		g[3].push_back(1);
		g[4].push_back(1);
		
		LCA lca(g);
		
		assert(lca.query(3, 4) == 1);
		assert(lca.query(3, 2) == 0);
		assert(lca.query(4, 2) == 0);
		assert(lca.query(1, 2) == 0);
		assert(lca.query(0, 0) == 0);
	}

	// Test 3: Star topology
	{
		//       0
		//     / | \
		//    1  2  3
		vector<vector<int>> g(4);
		g[0] = {1, 2, 3};
		g[1] = {0};
		g[2] = {0};
		g[3] = {0};
		
		LCA lca(g);
		
		assert(lca.query(1, 2) == 0);
		assert(lca.query(1, 3) == 0);
		assert(lca.query(2, 3) == 0);
		assert(lca.query(0, 1) == 0);
	}

	// Test 4: Deep tree
	{
		//  0-1-2-3-4-5-6-7-8-9
		vector<vector<int>> g(10);
		for (int i = 0; i < 9; i++) {
			g[i].push_back(i + 1);
			g[i + 1].push_back(i);
		}
		
		LCA lca(g);
		
		assert(lca.query(0, 9) == 0);
		assert(lca.query(3, 7) == 3);
		assert(lca.query(5, 8) == 5);
		assert(lca.query(2, 2) == 2);
	}

	// Test 5: Complex tree
	{
		//         0
		//        /|\
		//       1 2 3
		//      /|   |
		//     4 5   6
		//    /
		//   7
		vector<vector<int>> g(8);
		g[0] = {1, 2, 3};
		g[1] = {0, 4, 5};
		g[2] = {0};
		g[3] = {0, 6};
		g[4] = {1, 7};
		g[5] = {1};
		g[6] = {3};
		g[7] = {4};
		
		LCA lca(g);
		
		assert(lca.query(7, 5) == 1);
		assert(lca.query(7, 6) == 0);
		assert(lca.query(4, 5) == 1);
		assert(lca.query(2, 3) == 0);
		assert(lca.query(7, 7) == 7);
	}

	// Test 6: Symmetry of query
	{
		vector<vector<int>> g(6);
		g[0] = {1, 2};
		g[1] = {0, 3, 4};
		g[2] = {0, 5};
		g[3] = {1};
		g[4] = {1};
		g[5] = {2};
		
		LCA lca(g);
		
		// Query should be symmetric
		assert(lca.query(3, 5) == lca.query(5, 3));
		assert(lca.query(3, 4) == lca.query(4, 3));
		assert(lca.query(1, 2) == lca.query(2, 1));
	}

	cout << "All LCA (RMQ-based) tests passed!" << endl;
	return 0;
}


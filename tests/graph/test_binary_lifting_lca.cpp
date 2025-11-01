#include "../../graph/binary_lifting_lca.cpp"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

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

	// Test 5: Test up() function
	{
		//  0-1-2-3-4
		vector<vector<int>> g(5);
		for (int i = 0; i < 4; i++) {
			g[i].push_back(i + 1);
			g[i + 1].push_back(i);
		}
		
		LCA lca(g);
		
		assert(lca.up(4, 0) == 4);
		assert(lca.up(4, 1) == 3);
		assert(lca.up(4, 2) == 2);
		assert(lca.up(4, 3) == 1);
		assert(lca.up(4, 4) == 0);
	}

	// Test 6: Complex tree
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

	// Test 7: Large balanced tree
	{
		//           0
		//      /    |    \
		//     1     2     3
		//    /|\   /|\   /|\
		//   4 5 6 7 8 9 ...
		vector<vector<int>> g(40);
		g[0] = {1, 2, 3};
		for (int i = 1; i <= 3; i++) {
			g[i].push_back(0);
			for (int j = 0; j < 3; j++) {
				int child = 1 + (i - 1) * 3 + j + 3;
				if (child < 40) {
					g[i].push_back(child);
					g[child].push_back(i);
				}
			}
		}
		
		LCA lca(g);
		
		assert(lca.query(4, 5) == 1);
		assert(lca.query(4, 7) == 0);
		assert(lca.query(7, 8) == 2);
		assert(lca.query(0, 15) == 0);
	}

	cout << "All Binary Lifting LCA tests passed!" << endl;
	return 0;
}


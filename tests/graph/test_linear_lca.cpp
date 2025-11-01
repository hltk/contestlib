#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// Disable the main function in linear_lca.cpp
#define main main_disabled
#include "../../graph/linear_lca.cpp"
#undef main

int main() {
	// Test 1: Very simple tree
	{
		vector<vector<int>> g(2);
		g[0].push_back(1);
		
		LCA lca(g);
		
		assert(lca.query(0, 0) == 0);
		assert(lca.query(0, 1) == 0);
		assert(lca.query(1, 0) == 0);
	}

	// Test 2: Simple path of 3 nodes
	{
		vector<vector<int>> g(3);
		g[0].push_back(1);
		g[1].push_back(2);
		
		LCA lca(g);
		
		assert(lca.query(0, 0) == 0);
		assert(lca.query(1, 2) == 1);
		assert(lca.query(0, 2) == 0);
	}

	// Test 3: Binary tree
	{
		vector<vector<int>> g(3);
		g[0].push_back(1);
		g[0].push_back(2);
		
		LCA lca(g);
		
		assert(lca.query(1, 2) == 0);
		assert(lca.query(0, 1) == 0);
		assert(lca.query(0, 2) == 0);
	}

	// Test 4: Slightly larger tree
	{
		//     0
		//    / \
		//   1   2
		//  /
		// 3
		vector<vector<int>> g(4);
		g[0].push_back(1);
		g[0].push_back(2);
		g[1].push_back(3);
		
		LCA lca(g);
		
		assert(lca.query(1, 2) == 0);
		assert(lca.query(3, 2) == 0);
		assert(lca.query(1, 3) == 1);
	}

	cout << "All Linear LCA tests passed!" << endl;
	return 0;
}

#include "../../graph/toposort.cpp"
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	// Test 1: Linear chain
	{
		TopoSort ts(5);
		ts.addedge(0, 1);
		ts.addedge(1, 2);
		ts.addedge(2, 3);
		ts.addedge(3, 4);
		
		auto order = ts.sort();
		vector<int> expected = {0, 1, 2, 3, 4};
		assert(order == expected);
	}

	// Test 2: Diamond graph
	{
		TopoSort ts(4);
		ts.addedge(0, 1);
		ts.addedge(0, 2);
		ts.addedge(1, 3);
		ts.addedge(2, 3);
		
		auto order = ts.sort();
		assert(order.size() == 4);
		assert(order[0] == 0);
		assert(order[3] == 3);
	}

	// Test 3: Cycle detection
	{
		TopoSort ts(3);
		ts.addedge(0, 1);
		ts.addedge(1, 2);
		ts.addedge(2, 0);
		
		auto order = ts.sort();
		assert(order.empty());
	}

	// Test 4: Self loop
	{
		TopoSort ts(2);
		ts.addedge(0, 0);
		
		auto order = ts.sort();
		assert(order.empty());
	}

	// Test 5: Empty graph
	{
		TopoSort ts(0);
		auto order = ts.sort();
		assert(order.empty());
	}

	// Test 6: Single node
	{
		TopoSort ts(1);
		auto order = ts.sort();
		assert(order.size() == 1);
		assert(order[0] == 0);
	}

	// Test 7: Disconnected components
	{
		TopoSort ts(6);
		ts.addedge(0, 1);
		ts.addedge(2, 3);
		ts.addedge(3, 4);
		
		auto order = ts.sort();
		assert(order.size() == 6);
	}

	// Test 8: Complex DAG
	{
		TopoSort ts(6);
		ts.addedge(5, 2);
		ts.addedge(5, 0);
		ts.addedge(4, 0);
		ts.addedge(4, 1);
		ts.addedge(2, 3);
		ts.addedge(3, 1);
		
		auto order = ts.sort();
		assert(order.size() == 6);
	}

	// Test 9: Star graph
	{
		TopoSort ts(5);
		ts.addedge(0, 1);
		ts.addedge(0, 2);
		ts.addedge(0, 3);
		ts.addedge(0, 4);
		
		auto order = ts.sort();
		assert(order.size() == 5);
		assert(order[0] == 0);
	}

	// Test 10: Two nodes, cycle
	{
		TopoSort ts(2);
		ts.addedge(0, 1);
		ts.addedge(1, 0);
		
		auto order = ts.sort();
		assert(order.empty());
	}

	// Test 11: Longer cycle
	{
		TopoSort ts(5);
		ts.addedge(0, 1);
		ts.addedge(1, 2);
		ts.addedge(2, 3);
		ts.addedge(3, 1);
		ts.addedge(3, 4);
		
		auto order = ts.sort();
		assert(order.empty());
	}

	// Test 12: Tree structure
	{
		TopoSort ts(7);
		ts.addedge(0, 1);
		ts.addedge(0, 2);
		ts.addedge(1, 3);
		ts.addedge(1, 4);
		ts.addedge(2, 5);
		ts.addedge(5, 6);
		
		auto order = ts.sort();
		assert(order.size() == 7);
		assert(order[0] == 0);
	}

	// Test 13: Multiple sources
	{
		TopoSort ts(5);
		ts.addedge(0, 2);
		ts.addedge(1, 2);
		ts.addedge(2, 3);
		ts.addedge(2, 4);
		
		auto order = ts.sort();
		assert(order.size() == 5);
	}

	// Test 14: All isolated nodes
	{
		TopoSort ts(4);
		auto order = ts.sort();
		assert(order.size() == 4);
	}

	// Test 15: Large DAG
	{
		int n = 100;
		TopoSort ts(n);
		for (int i = 0; i < n - 1; i++) {
			ts.addedge(i, i + 1);
		}
		
		auto order = ts.sort();
		assert(order.size() == (size_t)n);
		for (int i = 0; i < n; i++) {
			assert(order[i] == i);
		}
	}

	cout << "All topological sort tests passed!" << endl;
	return 0;
}



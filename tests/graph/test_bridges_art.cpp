#include "../../graph/bridges_art.cpp"
#include <cassert>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int main() {
	// Test 1: Single node (no bridges, no articulation points)
	{
		BridgesArt ba(1);
		ba.run();
		assert(ba.bridges.size() == 0);
		int art_count = 0;
		for (int i = 0; i < ba.n; i++) {
			if (ba.is_art[i]) art_count++;
		}
		assert(art_count == 0);
	}

	// Test 2: Two nodes, one edge (bridge exists, no articulation points)
	{
		BridgesArt ba(2);
		ba.addedge(0, 1);
		ba.run();
		assert(ba.bridges.size() == 1);
		assert(ba.bridges[0] == make_pair(0, 1));
		assert(ba.is_bridge(0, 1));
		int art_count = 0;
		for (int i = 0; i < ba.n; i++) {
			if (ba.is_art[i]) art_count++;
		}
		assert(art_count == 0);
	}

	// Test 3: Three nodes in a path (two bridges)
	{
		BridgesArt ba(3);
		ba.addedge(0, 1);
		ba.addedge(1, 2);
		ba.run();
		assert(ba.bridges.size() == 2);
		assert(ba.is_bridge(0, 1));
		assert(ba.is_bridge(1, 2));
		vector<int> arts;
		for (int i = 0; i < ba.n; i++) {
			if (ba.is_art[i]) arts.push_back(i);
		}
		assert(arts.size() == 1);
		assert(arts[0] == 1);
		assert(ba.is_articulation_point(1));
	}

	// Test 4: Triangle (cycle, no bridges, no articulation points)
	{
		BridgesArt ba(3);
		ba.addedge(0, 1);
		ba.addedge(1, 2);
		ba.addedge(2, 0);
		ba.run();
		assert(ba.bridges.size() == 0);
		int art_count = 0;
		for (int i = 0; i < ba.n; i++) {
			if (ba.is_art[i]) art_count++;
		}
		assert(art_count == 0);
	}

	// Test 5: Two triangles connected by one edge
	// Triangle: 0-1-2-0
	// Triangle: 3-4-5-3
	// Connected: 2-3
	{
		BridgesArt ba(6);
		ba.addedge(0, 1);
		ba.addedge(1, 2);
		ba.addedge(2, 0);
		ba.addedge(3, 4);
		ba.addedge(4, 5);
		ba.addedge(5, 3);
		ba.addedge(2, 3);
		ba.run();
		assert(ba.bridges.size() == 1);
		assert(ba.bridges[0] == make_pair(2, 3));
		vector<int> arts;
		for (int i = 0; i < ba.n; i++) {
			if (ba.is_art[i]) arts.push_back(i);
		}
		assert(arts.size() == 2);
		assert(find(arts.begin(), arts.end(), 2) != arts.end());
		assert(find(arts.begin(), arts.end(), 3) != arts.end());
	}

	// Test 6: Star topology (center is articulation point)
	{
		BridgesArt ba(5);
		for (int i = 1; i < 5; i++) {
			ba.addedge(0, i);
		}
		ba.run();
		assert(ba.bridges.size() == 4);
		vector<int> arts;
		for (int i = 0; i < ba.n; i++) {
			if (ba.is_art[i]) arts.push_back(i);
		}
		assert(arts.size() == 1);
		assert(arts[0] == 0);
		assert(ba.is_articulation_point(0));
		for (int i = 1; i < 5; i++) {
			assert(ba.is_bridge(0, i));
			assert(!ba.is_articulation_point(i));
		}
	}

	// Test 7: Complete graph K4 (no bridges, no articulation points)
	{
		BridgesArt ba(4);
		ba.addedge(0, 1);
		ba.addedge(0, 2);
		ba.addedge(0, 3);
		ba.addedge(1, 2);
		ba.addedge(1, 3);
		ba.addedge(2, 3);
		ba.run();
		assert(ba.bridges.size() == 0);
		int art_count = 0;
		for (int i = 0; i < ba.n; i++) {
			if (ba.is_art[i]) art_count++;
		}
		assert(art_count == 0);
	}

	// Test 8: Tree (all edges are bridges)
	{
		BridgesArt ba(5);
		ba.addedge(0, 1);
		ba.addedge(0, 2);
		ba.addedge(1, 3);
		ba.addedge(1, 4);
		ba.run();
		assert(ba.bridges.size() == 4);
		vector<int> arts;
		for (int i = 0; i < ba.n; i++) {
			if (ba.is_art[i]) arts.push_back(i);
		}
		assert(arts.size() == 2);
		assert(find(arts.begin(), arts.end(), 0) != arts.end());
		assert(find(arts.begin(), arts.end(), 1) != arts.end());
	}

	// Test 9: Single edge (is a bridge)
	{
		BridgesArt ba(2);
		ba.addedge(0, 1);
		ba.run();
		assert(ba.bridges.size() == 1);
		assert(ba.bridges[0] == make_pair(0, 1));
		int art_count = 0;
		for (int i = 0; i < ba.n; i++) {
			if (ba.is_art[i]) art_count++;
		}
		assert(art_count == 0);
	}

	// Test 10: Path of 4 nodes
	{
		BridgesArt ba(4);
		ba.addedge(0, 1);
		ba.addedge(1, 2);
		ba.addedge(2, 3);
		ba.run();
		assert(ba.bridges.size() == 3);
		vector<int> arts;
		for (int i = 0; i < ba.n; i++) {
			if (ba.is_art[i]) arts.push_back(i);
		}
		assert(arts.size() == 2);
		assert(find(arts.begin(), arts.end(), 1) != arts.end());
		assert(find(arts.begin(), arts.end(), 2) != arts.end());
	}

	// Test 11: Multiple connected components
	{
		BridgesArt ba(6);
		// Component 1: 0-1-2
		ba.addedge(0, 1);
		ba.addedge(1, 2);
		// Component 2: 3-4-5
		ba.addedge(3, 4);
		ba.addedge(4, 5);
		ba.run();
		assert(ba.bridges.size() == 4);
		vector<int> arts;
		for (int i = 0; i < ba.n; i++) {
			if (ba.is_art[i]) arts.push_back(i);
		}
		assert(arts.size() == 2);
		assert(find(arts.begin(), arts.end(), 1) != arts.end());
		assert(find(arts.begin(), arts.end(), 4) != arts.end());
	}

	// Test 12: Cycle with one chord (creates cycle, no bridges)
	{
		BridgesArt ba(4);
		ba.addedge(0, 1);
		ba.addedge(1, 2);
		ba.addedge(2, 3);
		ba.addedge(3, 0);
		ba.addedge(0, 2);  // chord
		ba.run();
		assert(ba.bridges.size() == 0);
		int art_count = 0;
		for (int i = 0; i < ba.n; i++) {
			if (ba.is_art[i]) art_count++;
		}
		assert(art_count == 0);
	}

	// Test 13: Root with multiple children (root is articulation point)
	{
		BridgesArt ba(4);
		ba.addedge(0, 1);
		ba.addedge(0, 2);
		ba.addedge(0, 3);
		ba.run();
		vector<int> arts;
		for (int i = 0; i < ba.n; i++) {
			if (ba.is_art[i]) arts.push_back(i);
		}
		assert(arts.size() == 1);
		assert(arts[0] == 0);
		assert(ba.bridges.size() == 3);
	}

	// Test 14: Graph with multiple articulation points
	{
		BridgesArt ba(7);
		// Create a graph like: 0-1-2-3, with 1 and 2 as articulation points
		ba.addedge(0, 1);
		ba.addedge(1, 2);
		ba.addedge(2, 3);
		// Add some extra edges to create cycles
		ba.addedge(1, 4);
		ba.addedge(1, 5);
		ba.addedge(2, 6);
		ba.run();
		vector<int> arts;
		for (int i = 0; i < ba.n; i++) {
			if (ba.is_art[i]) arts.push_back(i);
		}
		sort(arts.begin(), arts.end());
		assert(arts.size() == 2);
		assert(arts[0] == 1);
		assert(arts[1] == 2);
	}

	std::cout << "All Bridges and Articulation Points tests passed!" << std::endl;
	return 0;
}


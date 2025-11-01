#include "../../graph/dinic.cpp"
#include <cassert>
#include <iostream>

using namespace std;

int main() {
	// Test 1: Simple single edge
	{
		// 0 --10--> 1
		Dinic flow(2);
		flow.addedge(0, 1, 10, true);
		
		ll result = flow.push(0, 1);
		assert(result == 10);
	}

	// Test 2: Two edges in series
	{
		// 0 --10--> 1 --5--> 2
		Dinic flow(3);
		flow.addedge(0, 1, 10, true);
		flow.addedge(1, 2, 5, true);
		
		ll result = flow.push(0, 2);
		assert(result == 5);  // Bottleneck is 5
	}

	// Test 3: Two parallel paths
	{
		// 0 --5--> 1 --10--> 3
		// 0 --7--> 2 --10--> 3
		Dinic flow(4);
		flow.addedge(0, 1, 5, true);
		flow.addedge(1, 3, 10, true);
		flow.addedge(0, 2, 7, true);
		flow.addedge(2, 3, 10, true);
		
		ll result = flow.push(0, 3);
		assert(result == 12);  // 5 + 7
	}

	// Test 4: No path exists
	{
		// 0    1 (disconnected)
		Dinic flow(2);
		
		ll result = flow.push(0, 1);
		assert(result == 0);
	}

	// Test 5: Bidirectional edge
	{
		// 0 <--10--> 1
		Dinic flow(2);
		flow.addedge(0, 1, 10, false);
		
		ll result = flow.push(0, 1);
		assert(result == 10);
	}

	// Test 6: Simple diamond
	{
		//     1
		//    / \
		//   0   3
		//    \ /
		//     2
		// Edges: 0->1 (10), 0->2 (10), 1->3 (10), 2->3 (10)
		Dinic flow(4);
		flow.addedge(0, 1, 10, true);
		flow.addedge(0, 2, 10, true);
		flow.addedge(1, 3, 10, true);
		flow.addedge(2, 3, 10, true);
		
		ll result = flow.push(0, 3);
		assert(result == 20);  // Both paths can carry 10 each
	}

	// Test 7: Zero capacity
	{
		// 0 --0--> 1
		Dinic flow(2);
		flow.addedge(0, 1, 0, true);
		
		ll result = flow.push(0, 1);
		assert(result == 0);
	}

	// Test 8: Source equals sink
	{
		Dinic flow(1);
		ll result = flow.push(0, 0);
		assert(result == 0);
	}

	cout << "All Dinic tests passed!" << endl;
	return 0;
}

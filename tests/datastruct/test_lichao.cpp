#include "../../datastruct/lichao.cpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
	// Test 1: Basic line addition and query
	{
		vector<int> xs = {0, 1, 2, 3, 4};
		LiChao<ll> tree(8, xs);
		
		// Add line y = 2x + 1
		tree.add_line(Line<ll>(2, 1));
		
		assert(tree.get_best(0) == 1);   // 2*0 + 1 = 1
		assert(tree.get_best(1) == 3);   // 2*1 + 1 = 3
		assert(tree.get_best(2) == 5);   // 2*2 + 1 = 5
		assert(tree.get_best(3) == 7);   // 2*3 + 1 = 7
	}

	// Test 2: Multiple lines, find minimum
	{
		vector<int> xs = {0, 1, 2, 3, 4, 5, 6, 7};
		LiChao<ll> tree(8, xs);
		
		// Add line y = x + 5
		tree.add_line(Line<ll>(1, 5));
		// Add line y = -x + 7
		tree.add_line(Line<ll>(-1, 7));
		
		// At x=0: min(5, 7) = 5
		// At x=1: min(6, 6) = 6
		// At x=2: min(7, 5) = 5
		// At x=3: min(8, 4) = 4
		assert(tree.get_best(0) == 5);
		assert(tree.get_best(1) == 6);
		assert(tree.get_best(2) == 5);
		assert(tree.get_best(3) == 4);
	}

	// Test 3: Horizontal line
	{
		vector<int> xs = {0, 1, 2, 3};
		LiChao<ll> tree(4, xs);
		
		// Add horizontal line y = 10
		tree.add_line(Line<ll>(0, 10));
		
		assert(tree.get_best(0) == 10);
		assert(tree.get_best(1) == 10);
		assert(tree.get_best(2) == 10);
		assert(tree.get_best(3) == 10);
	}

	// Test 4: Steep vs flat lines
	{
		vector<int> xs = {0, 1, 2, 3, 4, 5};
		LiChao<ll> tree(8, xs);
		
		// Add steep line: y = 10x + 1
		tree.add_line(Line<ll>(10, 1));
		// Add flat line: y = x + 3
		tree.add_line(Line<ll>(1, 3));
		
		// At x=0: min(1, 3) = 1
		// At x=1: min(11, 4) = 4
		// At x=2: min(21, 5) = 5
		assert(tree.get_best(0) == 1);
		assert(tree.get_best(1) == 4);
		assert(tree.get_best(2) == 5);
	}

	// Test 5: Negative slopes
	{
		vector<int> xs = {0, 1, 2, 3, 4};
		LiChao<ll> tree(8, xs);
		
		// Add line y = -2x + 10
		tree.add_line(Line<ll>(-2, 10));
		// Add line y = x
		tree.add_line(Line<ll>(1, 0));
		
		// At x=0: min(10, 0) = 0
		// At x=1: min(8, 1) = 1
		// At x=2: min(6, 2) = 2
		// At x=3: min(4, 3) = 3
		// At x=4: min(2, 4) = 2
		assert(tree.get_best(0) == 0);
		assert(tree.get_best(1) == 1);
		assert(tree.get_best(2) == 2);
		assert(tree.get_best(3) == 3);
		assert(tree.get_best(4) == 2);
	}

	// Test 6: Many lines with various slopes
	{
		vector<int> xs(100);
		for (int i = 0; i < 100; i++) xs[i] = i;
		
		LiChao<ll> tree(128, xs);
		
		// Add multiple lines
		tree.add_line(Line<ll>(1, 100));    // y = x + 100
		tree.add_line(Line<ll>(2, 0));      // y = 2x
		tree.add_line(Line<ll>(-1, 150));   // y = -x + 150
		tree.add_line(Line<ll>(0, 50));     // y = 50
		
		// At x=0: min(100, 0, 150, 50) = 0
		// At x=25: min(125, 50, 125, 50) = 50
		// At x=50: min(150, 100, 100, 50) = 50
		// At x=75: min(175, 150, 75, 50) = 50
		assert(tree.get_best(0) == 0);
		assert(tree.get_best(25) == 50);
		assert(tree.get_best(50) == 50);
		assert(tree.get_best(75) == 50);
	}

	// Test 7: Crossing lines
	{
		vector<int> xs = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		LiChao<ll> tree(16, xs);
		
		// Two lines that cross at x=5
		// Line 1: y = x (passes through origin)
		// Line 2: y = -x + 10 (passes through (0,10) and (10,0))
		tree.add_line(Line<ll>(1, 0));
		tree.add_line(Line<ll>(-1, 10));
		
		// At x=0: min(0, 10) = 0
		// At x=5: min(5, 5) = 5
		// At x=10: min(10, 0) = 0
		assert(tree.get_best(0) == 0);
		assert(tree.get_best(5) == 5);
		assert(tree.get_best(10) == 0);
	}

	// Test 8: Single point
	{
		vector<int> xs = {5};
		LiChao<ll> tree(1, xs);
		
		tree.add_line(Line<ll>(2, 3));  // y = 2x + 3
		assert(tree.get_best(0) == 13);  // 2*5 + 3 = 13
		
		tree.add_line(Line<ll>(1, 5));  // y = x + 5
		assert(tree.get_best(0) == 10);  // min(13, 10) = 10
	}

	// Test 9: Dynamic programming scenario
	{
		// Simulating a DP scenario where we add lines and query
		vector<int> xs(50);
		for (int i = 0; i < 50; i++) xs[i] = i;
		
		LiChao<ll> tree(64, xs);
		
		// Add initial line
		tree.add_line(Line<ll>(0, 100));
		
		// Simulate adding lines with decreasing intercepts
		for (int i = 0; i < 10; i++) {
			tree.add_line(Line<ll>(i, 100 - i * 5));
		}
		
		// Query at different points
		ll val0 = tree.get_best(0);
		ll val5 = tree.get_best(5);
		ll val10 = tree.get_best(10);
		
		// Values should be decreasing or equal as we find minimum
		assert(val0 <= 100);
		assert(val5 <= 100);
		assert(val10 <= 100);
	}

	// Test 10: Large coordinate space
	{
		vector<int> xs(1000);
		for (int i = 0; i < 1000; i++) xs[i] = i;
		
		LiChao<ll> tree(1024, xs);
		
		// Add several lines
		tree.add_line(Line<ll>(5, 1000));
		tree.add_line(Line<ll>(3, 2000));
		tree.add_line(Line<ll>(1, 3000));
		
		// At x=0: min(1000, 2000, 3000) = 1000
		// At x=500: min(3500, 3500, 3500) = 3500
		assert(tree.get_best(0) == 1000);
		
		// At some point, the line with smallest slope should win
		ll best = tree.get_best(999);
		assert(best <= 1000 + 5 * 999);  // Can't be worse than steepest line
	}

	cout << "All LiChao Tree tests passed!" << endl;
	return 0;
}


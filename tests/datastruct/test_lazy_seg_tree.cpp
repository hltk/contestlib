#include "../../datastruct/lazy_seg_tree.cpp"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// Naive implementation for verification
long naive_sum(const vector<long>& arr, int l, int r) {
	long sum = 0;
	for (int i = l; i < r; i++) {
		sum += arr[i];
	}
	return sum;
}

int main() {
	// Test 1: Basic range add and query
	{
		SegmentTree tree(8);
		
		tree.change(0, 3, 5);  // Add 5 to [0, 3)
		assert(tree.query(0, 3) == 15);  // 5 * 3 = 15
		assert(tree.query(3, 8) == 0);
	}

	// Test 2: Overlapping range updates
	{
		SegmentTree tree(8);
		
		tree.change(0, 4, 10);  // Add 10 to [0, 4)
		tree.change(2, 6, 5);   // Add 5 to [2, 6)
		
		// [0, 2): 10 each = 20
		// [2, 4): 15 each = 30
		// [4, 6): 5 each = 10
		assert(tree.query(0, 2) == 20);
		assert(tree.query(2, 4) == 30);
		assert(tree.query(4, 6) == 10);
		assert(tree.query(0, 6) == 60);
	}

	// Test 3: Single element updates and queries
	{
		SegmentTree tree(4);
		
		tree.change(0, 1, 5);
		tree.change(1, 2, 10);
		tree.change(2, 3, 15);
		
		assert(tree.query(0, 1) == 5);
		assert(tree.query(1, 2) == 10);
		assert(tree.query(2, 3) == 15);
		assert(tree.query(0, 3) == 30);
	}

	// Test 4: Multiple updates on same range
	{
		SegmentTree tree(4);
		
		tree.change(0, 2, 5);
		tree.change(0, 2, 3);
		tree.change(0, 2, 2);
		
		// Each element should have 5 + 3 + 2 = 10
		assert(tree.query(0, 2) == 20);
	}

	// Test 5: Full range update
	{
		SegmentTree tree(8);
		
		tree.change(0, 8, 7);
		assert(tree.query(0, 8) == 56);  // 7 * 8 = 56
		
		tree.change(0, 8, 3);
		assert(tree.query(0, 8) == 80);  // 10 * 8 = 80
	}

	// Test 6: Lazy propagation test
	{
		SegmentTree tree(16);
		
		tree.change(0, 8, 10);
		tree.change(8, 16, 20);
		
		assert(tree.query(0, 8) == 80);
		assert(tree.query(8, 16) == 160);
		assert(tree.query(0, 16) == 240);
		
		// Now make more queries to ensure propagation works
		assert(tree.query(0, 4) == 40);
		assert(tree.query(4, 8) == 40);
		assert(tree.query(8, 12) == 80);
		assert(tree.query(12, 16) == 80);
	}

	// Test 7: Negative values
	{
		SegmentTree tree(8);
		
		tree.change(0, 4, 10);
		tree.change(2, 6, -5);
		
		// [0, 2): 10 each = 20
		// [2, 4): 5 each = 10
		// [4, 6): -5 each = -10
		assert(tree.query(0, 2) == 20);
		assert(tree.query(2, 4) == 10);
		assert(tree.query(4, 6) == -10);
		assert(tree.query(0, 6) == 20);
	}

	// Test 8: Empty range query
	{
		SegmentTree tree(8);
		
		tree.change(0, 8, 10);
		assert(tree.query(3, 3) == 0);  // Empty range
	}

	// Test 9: Complex pattern
	{
		SegmentTree tree(16);
		vector<long> arr(16, 0);
		
		// Perform several range updates
		tree.change(0, 8, 1);
		for (int i = 0; i < 8; i++) arr[i] += 1;
		
		tree.change(4, 12, 2);
		for (int i = 4; i < 12; i++) arr[i] += 2;
		
		tree.change(2, 6, 3);
		for (int i = 2; i < 6; i++) arr[i] += 3;
		
		tree.change(8, 16, 4);
		for (int i = 8; i < 16; i++) arr[i] += 4;
		
		// Verify various range queries
		for (int l = 0; l < 16; l++) {
			for (int r = l + 1; r <= 16; r++) {
				assert(tree.query(l, r) == naive_sum(arr, l, r));
			}
		}
	}

	// Test 10: Large tree stress test
	{
		SegmentTree tree(128);
		vector<long> arr(128, 0);
		
		// Random-ish updates
		tree.change(0, 32, 5);
		for (int i = 0; i < 32; i++) arr[i] += 5;
		
		tree.change(16, 64, 3);
		for (int i = 16; i < 64; i++) arr[i] += 3;
		
		tree.change(48, 96, -2);
		for (int i = 48; i < 96; i++) arr[i] += -2;
		
		tree.change(32, 128, 7);
		for (int i = 32; i < 128; i++) arr[i] += 7;
		
		// Verify several queries
		assert(tree.query(0, 128) == naive_sum(arr, 0, 128));
		assert(tree.query(0, 64) == naive_sum(arr, 0, 64));
		assert(tree.query(64, 128) == naive_sum(arr, 64, 128));
		assert(tree.query(32, 96) == naive_sum(arr, 32, 96));
	}

	// Test 11: Alternating updates
	{
		SegmentTree tree(8);
		
		for (int i = 0; i < 8; i++) {
			tree.change(i, i + 1, i + 1);
		}
		
		// Each position i has value i+1
		long expected = 0;
		for (int i = 0; i < 8; i++) {
			expected += i + 1;
		}
		assert(tree.query(0, 8) == expected);  // 1+2+3+4+5+6+7+8 = 36
	}

	cout << "All Lazy Segment Tree tests passed!" << endl;
	return 0;
}


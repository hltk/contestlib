#include "../../datastruct/treap.cpp"
#include <cassert>
#include <iostream>

using namespace std;

int main() {
	// Test 1: Basic merge and split
	{
		Treap* a = new Treap(5);
		Treap* b = new Treap(10);
		
		Treap* merged = Treap::merge(a, b);
		assert(merged != nullptr);
		
		auto [left, right] = Treap::split(merged, 1);
		assert(left != nullptr);
		assert(right != nullptr);
	}

	// Test 2: Build a sequence and split
	{
		Treap* root = new Treap(1);
		root = Treap::merge(root, new Treap(2));
		root = Treap::merge(root, new Treap(3));
		root = Treap::merge(root, new Treap(4));
		root = Treap::merge(root, new Treap(5));
		
		assert(root != nullptr);
		
		auto [left, right] = Treap::split(root, 3);
		assert(left != nullptr);
		assert(right != nullptr);
	}

	// Test 3: Split at beginning
	{
		Treap* root = new Treap(1);
		root = Treap::merge(root, new Treap(2));
		root = Treap::merge(root, new Treap(3));
		
		auto [left, right] = Treap::split(root, 0);
		assert(left == nullptr);
		assert(right != nullptr);
	}

	// Test 4: Split at end
	{
		Treap* root = new Treap(1);
		root = Treap::merge(root, new Treap(2));
		root = Treap::merge(root, new Treap(3));
		
		auto [left, right] = Treap::split(root, 3);
		assert(left != nullptr);
		assert(right == nullptr);
	}

	// Test 5: Multiple splits and merges
	{
		Treap* root = new Treap(1);
		for (int i = 2; i <= 10; i++) {
			root = Treap::merge(root, new Treap(i));
		}
		
		assert(root != nullptr);
		
		auto [a, b] = Treap::split(root, 5);
		auto [c, d] = Treap::split(b, 3);
		
		assert(a != nullptr);
		assert(c != nullptr);
		// d might be null or not, depends on split behavior
		
		Treap* merged = Treap::merge(a, Treap::merge(c, d));
		assert(merged != nullptr);
	}

	// Test 6: Merge null pointers
	{
		Treap* a = nullptr;
		Treap* b = new Treap(5);
		
		Treap* merged = Treap::merge(a, b);
		assert(merged != nullptr);
		
		merged = Treap::merge(merged, nullptr);
		assert(merged != nullptr);
	}

	// Test 7: Split null pointer
	{
		Treap* root = nullptr;
		auto [left, right] = Treap::split(root, 5);
		
		assert(left == nullptr);
		assert(right == nullptr);
	}

	// Test 8: Single element operations
	{
		Treap* root = new Treap(42);
		
		assert(root != nullptr);
		
		auto [left, right] = Treap::split(root, 0);
		assert(left == nullptr);
		assert(right != nullptr);
	}

	// Test 9: Build larger sequence
	{
		Treap* root = nullptr;
		for (int i = 0; i < 100; i++) {
			root = Treap::merge(root, new Treap(i));
		}
		
		assert(root != nullptr);
		
		auto [left, right] = Treap::split(root, 50);
		assert(left != nullptr);
		assert(right != nullptr);
	}

	// Test 10: Repeated split and merge
	{
		Treap* root = new Treap(1);
		root = Treap::merge(root, new Treap(2));
		root = Treap::merge(root, new Treap(3));
		root = Treap::merge(root, new Treap(4));
		
		for (int i = 0; i < 3; i++) {
			auto [l, r] = Treap::split(root, 2);
			assert(l != nullptr);
			assert(r != nullptr);
			root = Treap::merge(l, r);
			assert(root != nullptr);
		}
	}

	// Test 11: Insert in middle (split-insert-merge pattern)
	{
		Treap* root = new Treap(1);
		root = Treap::merge(root, new Treap(2));
		root = Treap::merge(root, new Treap(4));
		root = Treap::merge(root, new Treap(5));
		
		// Insert 3 between 2 and 4 (at position 2)
		auto [left, right] = Treap::split(root, 2);
		left = Treap::merge(left, new Treap(3));
		root = Treap::merge(left, right);
		
		assert(root != nullptr);
	}

	// Test 12: Remove from middle (split pattern)
	{
		Treap* root = new Treap(1);
		for (int i = 2; i <= 10; i++) {
			root = Treap::merge(root, new Treap(i));
		}
		
		// Remove element at position 5
		auto [left, right] = Treap::split(root, 5);
		auto [mid, rest] = Treap::split(right, 1);
		root = Treap::merge(left, rest);
		
		assert(root != nullptr);
	}

	// Test 13: Merge many nodes
	{
		Treap* root = nullptr;
		for (int i = 0; i < 1000; i++) {
			root = Treap::merge(root, new Treap(i));
		}
		assert(root != nullptr);
		
		// Split in half
		auto [l, r] = Treap::split(root, 500);
		assert(l != nullptr);
		assert(r != nullptr);
	}

	// Test 14: Complex sequence of operations
	{
		Treap* root = nullptr;
		
		// Build sequence
		for (int i = 0; i < 20; i++) {
			root = Treap::merge(root, new Treap(i * 10));
		}
		
		// Split into 4 parts
		auto [p1, temp1] = Treap::split(root, 5);
		auto [p2, temp2] = Treap::split(temp1, 5);
		auto [p3, p4] = Treap::split(temp2, 5);
		
		// Merge back in different order
		root = Treap::merge(p1, p3);
		root = Treap::merge(root, p2);
		root = Treap::merge(root, p4);
		
		assert(root != nullptr);
	}

	cout << "All Treap tests passed!" << endl;
	return 0;
}

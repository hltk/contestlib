#include <vector>
using namespace std;

#include "../../misc/vec.cpp"
#include <cassert>
#include <iostream>

int main() {
	// Test 1: 1D vector
	{
		auto v = create(5, 0);
		assert(v.size() == 5);
		for (int x : v) assert(x == 0);
	}

	// Test 2: 2D vector
	{
		auto v = create(3, 4, 0);
		assert(v.size() == 3);
		for (auto& row : v) {
			assert(row.size() == 4);
			for (int x : row) assert(x == 0);
		}
	}

	// Test 3: 3D vector
	{
		auto v = create(2, 3, 4, -1);
		assert(v.size() == 2);
		for (auto& plane : v) {
			assert(plane.size() == 3);
			for (auto& row : plane) {
				assert(row.size() == 4);
				for (int x : row) assert(x == -1);
			}
		}
	}

	// Test 4: Different initial values
	{
		auto v = create(10, 42);
		for (int x : v) assert(x == 42);
	}

	// Test 5: 2D with different value
	{
		auto v = create(2, 3, 99);
		for (auto& row : v) {
			for (int x : row) {
				assert(x == 99);
			}
		}
	}

	// Test 6: Single element
	{
		auto v = create(1, 7);
		assert(v.size() == 1);
		assert(v[0] == 7);
	}

	// Test 7: Verify independence of rows
	{
		auto v = create(3, 3, 0);
		v[0][0] = 1;
		v[1][1] = 2;
		v[2][2] = 3;
		
		assert(v[0][0] == 1);
		assert(v[0][1] == 0);
		assert(v[1][0] == 0);
		assert(v[1][1] == 2);
		assert(v[2][2] == 3);
	}

	// Test 8: Large dimensions
	{
		auto v = create(100, 0);
		assert(v.size() == 100);
		
		auto v2 = create(50, 50, 1);
		assert(v2.size() == 50);
		assert(v2[0].size() == 50);
	}

	// Test 9: 4D vector
	{
		auto v = create(2, 2, 2, 2, 5);
		assert(v.size() == 2);
		assert(v[0].size() == 2);
		assert(v[0][0].size() == 2);
		assert(v[0][0][0].size() == 2);
		assert(v[0][0][0][0] == 5);
	}

	// Test 10: Boolean vectors
	{
		auto v = create(5, false);
		for (bool x : v) assert(x == false);
		
		auto v2 = create(3, 3, true);
		for (auto& row : v2) {
			for (bool x : row) {
				assert(x == true);
			}
		}
	}

	cout << "All Vec tests passed!" << endl;
	return 0;
}


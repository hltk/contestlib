#include <vector>
using namespace std;

#include "../../misc/vec.cpp"
#include <cassert>
#include <iostream>

int main() {
	// Test 1: 1D vector with int
	{
		auto v = create(5, 0);
		assert(v.size() == 5);
		for (int x : v) {
			assert(x == 0);
		}
	}

	// Test 2: 1D vector with non-zero value
	{
		auto v = create(3, 42);
		assert(v.size() == 3);
		for (int x : v) {
			assert(x == 42);
		}
	}

	// Test 3: 2D vector (matrix)
	{
		auto v = create(3, 4, 0);
		assert(v.size() == 3);
		for (const auto& row : v) {
			assert(row.size() == 4);
			for (int x : row) {
				assert(x == 0);
			}
		}
	}

	// Test 4: 2D vector with non-zero value
	{
		auto v = create(2, 3, 7);
		assert(v.size() == 2);
		for (const auto& row : v) {
			assert(row.size() == 3);
			for (int x : row) {
				assert(x == 7);
			}
		}
	}
 
	// Test 5: 3D vector (tensor)
	{
		auto v = create(2, 3, 4, 0);
		assert(v.size() == 2);
		for (const auto& layer : v) {
			assert(layer.size() == 3);
			for (const auto& row : layer) {
				assert(row.size() == 4);
				for (int x : row) {
					assert(x == 0);
				}
			}
		}
	}

	// Test 6: 3D vector with non-zero value
	{
		auto v = create(2, 2, 2, 5);
		assert(v.size() == 2);
		for (const auto& layer : v) {
			assert(layer.size() == 2);
			for (const auto& row : layer) {
				assert(row.size() == 2);
				for (int x : row) {
					assert(x == 5);
				}
			}
		}
	}

	// Test 7: 4D vector
	{
		auto v = create(2, 2, 2, 2, 1);
		assert(v.size() == 2);
		for (const auto& dim1 : v) {
			assert(dim1.size() == 2);
			for (const auto& dim2 : dim1) {
				assert(dim2.size() == 2);
				for (const auto& dim3 : dim2) {
					assert(dim3.size() == 2);
					for (int x : dim3) {
						assert(x == 1);
					}
				}
			}
		}
	}

	// Test 8: Empty 1D vector
	{
		auto v = create(0, 0);
		assert(v.size() == 0);
	}

	// Test 9: Single element
	{
		auto v = create(1, 99);
		assert(v.size() == 1);
		assert(v[0] == 99);
	}

	// Test 10: Modify and check independence
	{
		auto v = create(3, 3, 0);
		v[0][0] = 5;
		v[1][1] = 7;
		v[2][2] = 9;
		
		assert(v[0][0] == 5);
		assert(v[0][1] == 0);  // Other elements unchanged
		assert(v[1][0] == 0);
		assert(v[1][1] == 7);
		assert(v[2][2] == 9);
	}

	// Test 11: 2D with different dimensions
	{
		auto v = create(5, 10, -1);
		assert(v.size() == 5);
		assert(v[0].size() == 10);
		assert(v[4].size() == 10);
		assert(v[0][0] == -1);
		assert(v[4][9] == -1);
	}

	// Test 12: With long long
	{
		auto v = create(2, 3, 1000000000LL);
		assert(v.size() == 2);
		assert(v[0].size() == 3);
		assert(v[0][0] == 1000000000LL);
	}

	// Test 13: With double
	{
		auto v = create(2, 2, 3.14);
		assert(v.size() == 2);
		assert(v[0].size() == 2);
		assert(v[0][0] == 3.14);
		assert(v[1][1] == 3.14);
	}

	// Test 14: Large 2D
	{
		auto v = create(100, 100, 0);
		assert(v.size() == 100);
		assert(v[0].size() == 100);
		assert(v[99].size() == 100);
		assert(v[50][50] == 0);
	}

	// Test 15: Verify modification doesn't affect other rows (deep copy)
	{
		auto v = create(3, 3, 0);
		v[0][0] = 1;
		v[0][1] = 2;
		v[0][2] = 3;
		
		// Other rows should still be all zeros
		for (int j = 0; j < 3; ++j) {
			assert(v[1][j] == 0);
			assert(v[2][j] == 0);
		}
	}

	// Test 16: 3D modification independence
	{
		auto v = create(2, 2, 2, 0);
		v[0][0][0] = 1;
		
		// Check other elements are still 0
		assert(v[0][0][1] == 0);
		assert(v[0][1][0] == 0);
		assert(v[1][0][0] == 0);
		assert(v[1][1][1] == 0);
	}

	// Test 17: Non-square matrices
	{
		auto v = create(2, 5, 8);
		assert(v.size() == 2);
		assert(v[0].size() == 5);
		assert(v[1].size() == 5);
		
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 5; ++j) {
				assert(v[i][j] == 8);
			}
		}
	}

	cout << "All vec tests passed!" << endl;
	return 0;
}

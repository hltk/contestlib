#include "../../datastruct/monotonic_queue.cpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	// Test 1: Basic min queue operations
	{
		MonotonicQueue<int, less<int>> mq;
		
		mq.push(5);
		assert(mq.get() == 5);
		
		mq.push(3);
		assert(mq.get() == 3);
		
		mq.push(7);
		assert(mq.get() == 3);
		
		mq.pop();  // Remove 5
		assert(mq.get() == 3);
		
		mq.pop();  // Remove 3
		assert(mq.get() == 7);
	}

	// Test 2: Max queue operations
	{
		MonotonicQueue<int, greater<int>> mq;
		
		mq.push(5);
		assert(mq.get() == 5);
		
		mq.push(8);
		assert(mq.get() == 8);
		
		mq.push(3);
		assert(mq.get() == 8);
		
		mq.pop();  // Remove 5
		assert(mq.get() == 8);
		
		mq.pop();  // Remove 8
		assert(mq.get() == 3);
	}

	// Test 3: Sliding window minimum
	{
		vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
		int k = 3;
		vector<int> result;
		
		MonotonicQueue<int, less<int>> mq;
		
		// Initialize window
		for (int i = 0; i < k; i++) {
			mq.push(arr[i]);
		}
		result.push_back(mq.get());
		
		// Slide window
		for (int i = k; i < (int)arr.size(); i++) {
			mq.pop();
			mq.push(arr[i]);
			result.push_back(mq.get());
		}
		
		vector<int> expected = {-1, -3, -3, -3, 3, 3};
		assert(result == expected);
	}

	// Test 4: Sliding window maximum
	{
		vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
		int k = 3;
		vector<int> result;
		
		MonotonicQueue<int, greater<int>> mq;
		
		// Initialize window
		for (int i = 0; i < k; i++) {
			mq.push(arr[i]);
		}
		result.push_back(mq.get());
		
		// Slide window
		for (int i = k; i < (int)arr.size(); i++) {
			mq.pop();
			mq.push(arr[i]);
			result.push_back(mq.get());
		}
		
		vector<int> expected = {3, 3, 5, 5, 6, 7};
		assert(result == expected);
	}

	// Test 5: Increasing sequence (min queue)
	{
		MonotonicQueue<int, less<int>> mq;
		
		for (int i = 1; i <= 10; i++) {
			mq.push(i);
			assert(mq.get() == 1);
		}
		
		for (int i = 1; i <= 10; i++) {
			assert(mq.get() == i);
			mq.pop();
		}
	}

	// Test 6: Decreasing sequence (min queue)
	{
		MonotonicQueue<int, less<int>> mq;
		
		for (int i = 10; i >= 1; i--) {
			mq.push(i);
			assert(mq.get() == i);
		}
		
		for (int i = 10; i >= 1; i--) {
			assert(mq.get() == 1);
			mq.pop();
		}
	}

	// Test 7: All same values
	{
		MonotonicQueue<int, less<int>> mq;
		
		for (int i = 0; i < 10; i++) {
			mq.push(5);
			assert(mq.get() == 5);
		}
		
		for (int i = 0; i < 10; i++) {
			assert(mq.get() == 5);
			mq.pop();
		}
	}

	// Test 8: Alternating values
	{
		MonotonicQueue<int, less<int>> mq;
		
		mq.push(1);
		mq.push(2);
		mq.push(1);
		mq.push(2);
		
		assert(mq.get() == 1);
		mq.pop();
		assert(mq.get() == 1);
		mq.pop();
		assert(mq.get() == 1);
		mq.pop();
		assert(mq.get() == 2);
	}

	// Test 9: Large window
	{
		vector<int> arr(1000);
		for (int i = 0; i < 1000; i++) {
			arr[i] = i % 100;
		}
		
		MonotonicQueue<int, less<int>> mq;
		
		// Window size 100
		for (int i = 0; i < 100; i++) {
			mq.push(arr[i]);
		}
		assert(mq.get() == 0);
		
		for (int i = 100; i < 1000; i++) {
			mq.pop();
			mq.push(arr[i]);
			assert(mq.get() == 0);
		}
	}

	// Test 10: Single element
	{
		MonotonicQueue<int, less<int>> mq;
		
		mq.push(42);
		assert(mq.get() == 42);
		
		mq.pop();
		mq.push(100);
		assert(mq.get() == 100);
	}

	cout << "All Monotonic Queue tests passed!" << endl;
	return 0;
}


#include <chrono>
#include <iostream>
#include <cassert>

using namespace std;
using namespace std::chrono;

// Include the timer snippet
auto start = high_resolution_clock::now();
auto stop = high_resolution_clock::now();
auto elapsed = duration_cast<milliseconds>(stop - start);

int main() {
	// Test 1: Basic timer usage
	{
		auto t1 = high_resolution_clock::now();
		
		// Do some work (simulate with a short loop)
		volatile int sum = 0;
		for (int i = 0; i < 1000; i++) {
			sum += i;
		}
		
		auto t2 = high_resolution_clock::now();
		auto dur = duration_cast<microseconds>(t2 - t1);
		
		// Duration should be non-negative
		assert(dur.count() >= 0);
	}

	// Test 2: Measure something that takes time
	{
		auto t1 = high_resolution_clock::now();
		
		// Do more work
		volatile long long sum = 0;
		for (int i = 0; i < 10000; i++) {
			sum += i * i;
		}
		
		auto t2 = high_resolution_clock::now();
		auto dur = duration_cast<microseconds>(t2 - t1);
		
		// Should take some measurable time
		assert(dur.count() >= 0);
		
		cout << "10000 iterations took " << dur.count() << " microseconds" << endl;
	}

	// Test 3: Different duration units
	{
		auto t1 = high_resolution_clock::now();
		
		volatile int sum = 0;
		for (int i = 0; i < 1000; i++) {
			sum += i;
		}
		
		auto t2 = high_resolution_clock::now();
		
		auto nanos = duration_cast<nanoseconds>(t2 - t1);
		auto micros = duration_cast<microseconds>(t2 - t1);
		auto millis = duration_cast<milliseconds>(t2 - t1);
		
		// Nanoseconds should be >= microseconds * 1000 (approximately)
		assert(nanos.count() >= micros.count());
		assert(micros.count() >= millis.count());
		
		cout << "Measured in nanos: " << nanos.count() << endl;
		cout << "Measured in micros: " << micros.count() << endl;
		cout << "Measured in millis: " << millis.count() << endl;
	}

	// Test 4: Global timer variables
	{
		start = high_resolution_clock::now();
		
		volatile int sum = 0;
		for (int i = 0; i < 5000; i++) {
			sum += i;
		}
		
		stop = high_resolution_clock::now();
		elapsed = duration_cast<milliseconds>(stop - start);
		
		assert(elapsed.count() >= 0);
		cout << "Global timer: " << elapsed.count() << " milliseconds" << endl;
	}

	// Test 5: Multiple consecutive measurements
	{
		vector<long long> times;
		
		for (int run = 0; run < 5; run++) {
			auto t1 = high_resolution_clock::now();
			
			volatile int sum = 0;
			for (int i = 0; i < 1000; i++) {
				sum += i;
			}
			
			auto t2 = high_resolution_clock::now();
			auto dur = duration_cast<microseconds>(t2 - t1);
			
			times.push_back(dur.count());
		}
		
		// All measurements should be non-negative
		for (auto t : times) {
			assert(t >= 0);
		}
		
		cout << "5 consecutive runs (microseconds): ";
		for (auto t : times) {
			cout << t << " ";
		}
		cout << endl;
	}

	cout << "All Timer tests passed!" << endl;
	return 0;
}


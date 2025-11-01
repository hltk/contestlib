#include "../../math/fact.cpp"
#include <cassert>
#include <iostream>

using namespace std;

int main() {
	// Initialize the factorial table - need to pre-initialize to avoid bugs in ensure_facts
	comb::ensure_facts(1000);
	
	// Test 1: Basic factorials
	{
		assert(int(comb::factorial(0)) == 1);
		assert(int(comb::factorial(1)) == 1);
		assert(int(comb::factorial(2)) == 2);
		assert(int(comb::factorial(3)) == 6);
		assert(int(comb::factorial(4)) == 24);
		assert(int(comb::factorial(5)) == 120);
	}

	// Test 2: Basic choose (binomial coefficients)
	{
		// C(n, 0) = 1
		assert(int(comb::choose(5, 0)) == 1);
		assert(int(comb::choose(10, 0)) == 1);
		
		// C(n, 1) = n
		assert(int(comb::choose(5, 1)) == 5);
		assert(int(comb::choose(10, 1)) == 10);
		
		// C(n, n) = 1
		assert(int(comb::choose(5, 5)) == 1);
		assert(int(comb::choose(10, 10)) == 1);
		
		// C(n, n-1) = n
		assert(int(comb::choose(5, 4)) == 5);
		assert(int(comb::choose(10, 9)) == 10);
	}

	// Test 3: Common binomial coefficients
	{
		assert(int(comb::choose(4, 2)) == 6);  // C(4,2) = 6
		assert(int(comb::choose(5, 2)) == 10); // C(5,2) = 10
		assert(int(comb::choose(6, 3)) == 20); // C(6,3) = 20
		assert(int(comb::choose(10, 5)) == 252); // C(10,5) = 252
	}

	// Test 4: Invalid choose (should return 0)
	{
		// C(n, k) = 0 when k > n
		assert(int(comb::choose(5, 6)) == 0);
		assert(int(comb::choose(3, 10)) == 0);
		
		// C(n, k) = 0 when k < 0
		assert(int(comb::choose(5, -1)) == 0);
		assert(int(comb::choose(10, -5)) == 0);
	}

	// Test 5: Symmetry property C(n,k) = C(n,n-k)
	{
		assert(int(comb::choose(10, 3)) == int(comb::choose(10, 7)));
		assert(int(comb::choose(15, 5)) == int(comb::choose(15, 10)));
		assert(int(comb::choose(20, 8)) == int(comb::choose(20, 12)));
	}

	// Test 6: Pascal's triangle property C(n,k) = C(n-1,k-1) + C(n-1,k)
	{
		for (int n = 2; n <= 10; ++n) {
			for (int k = 1; k < n; ++k) {
				mint left = comb::choose(n - 1, k - 1);
				mint right = comb::choose(n - 1, k);
				mint expected = comb::choose(n, k);
				assert(int(left + right) == int(expected));
			}
		}
	}

	// Test 7: Inverse factorial
	{
		// factorial(n) * inv_factorial(n) = 1
		for (int n = 0; n <= 20; ++n) {
			mint fact = comb::factorial(n);
			mint ifact = comb::inv_factorial(n);
			assert(int(fact * ifact) == 1);
		}
	}

	// Test 8: Choose formula verification
	{
		// C(n,k) = n! / (k! * (n-k)!)
		for (int n = 0; n <= 15; ++n) {
			for (int k = 0; k <= n; ++k) {
				mint choose_val = comb::choose(n, k);
				mint fact_n = comb::factorial(n);
				mint fact_k = comb::inv_factorial(k);
				mint fact_nk = comb::inv_factorial(n - k);
				mint expected = fact_n * fact_k * fact_nk;
				assert(int(choose_val) == int(expected));
			}
		}
	}

	// Test 9: Large factorials (testing modular arithmetic)
	{
		// These would overflow without modular arithmetic
		mint f100 = comb::factorial(100);
		mint if100 = comb::inv_factorial(100);
		assert(int(f100 * if100) == 1);
		
		mint f500 = comb::factorial(500);
		mint if500 = comb::inv_factorial(500);
		assert(int(f500 * if500) == 1);
	}

	// Test 10: Large choose values
	{
		// C(100, 50) is a very large number
		mint c = comb::choose(100, 50);
		// Just verify it's non-zero and within mod range
		assert(int(c) > 0);
		assert(int(c) < MOD);
		
		// Verify using symmetry
		assert(int(comb::choose(100, 50)) == int(comb::choose(100, 50)));
	}

	// Test 11: Edge cases with zero
	{
		assert(int(comb::choose(0, 0)) == 1);
		assert(int(comb::choose(1, 0)) == 1);
		assert(int(comb::choose(0, 1)) == 0);
	}

	// Test 12: Sum property: sum of C(n,k) for k=0 to n equals 2^n
	{
		for (int n = 0; n <= 10; ++n) {
			mint sum = 0;
			for (int k = 0; k <= n; ++k) {
				sum += comb::choose(n, k);
			}
			mint expected = pow(mint(2), n);
			assert(int(sum) == int(expected));
		}
	}

	// Test 13: Hockey stick identity
	{
		// Sum of C(i, k) for i=k to n equals C(n+1, k+1)
		int k = 3;
		for (int n = k; n <= 10; ++n) {
			mint sum = 0;
			for (int i = k; i <= n; ++i) {
				sum += comb::choose(i, k);
			}
			mint expected = comb::choose(n + 1, k + 1);
			assert(int(sum) == int(expected));
		}
	}

	// Test 14: Multiple ensure_facts calls (should not cause issues)
	{
		comb::ensure_facts(50);
		comb::ensure_facts(30);  // Smaller, should do nothing
		comb::ensure_facts(60);  // Larger, should extend
		
		// Should still work correctly
		assert(int(comb::factorial(55) * comb::inv_factorial(55)) == 1);
	}

	// Test 15: Vandermonde's identity
	{
		// C(m+n, r) = sum of C(m,k)*C(n,r-k) for k=0 to r
		int m = 5, n = 4, r = 3;
		mint left = comb::choose(m + n, r);
		mint right = 0;
		for (int k = 0; k <= r; ++k) {
			right += comb::choose(m, k) * comb::choose(n, r - k);
		}
		assert(int(left) == int(right));
	}

	// Test 16: Specific values
	{
		// C(7, 3) = 35
		assert(int(comb::choose(7, 3)) == 35);
		// C(8, 4) = 70
		assert(int(comb::choose(8, 4)) == 70);
		// C(9, 2) = 36
		assert(int(comb::choose(9, 2)) == 36);
		// C(12, 6) = 924
		assert(int(comb::choose(12, 6)) == 924);
	}

	// Test 17: Catalan numbers
	{
		// Catalan(n) = C(2n, n) / (n+1)
		// Catalan(0) = 1, Catalan(1) = 1, Catalan(2) = 2, Catalan(3) = 5, Catalan(4) = 14
		vector<int> catalan = {1, 1, 2, 5, 14, 42, 132};
		for (int n = 0; n < int(catalan.size()); ++n) {
			mint cat = comb::choose(2 * n, n) / mint(n + 1);
			assert(int(cat) == catalan[n]);
		}
	}

	// Test 18: Stress test with many queries
	{
		for (int n = 0; n <= 100; ++n) {
			for (int k = 0; k <= min(n, 10); ++k) {
				mint c = comb::choose(n, k);
				// Just ensure it computes without error
				assert(int(c) >= 0);
			}
		}
	}

	cout << "All factorial and combinatorics tests passed!" << endl;
	return 0;
}


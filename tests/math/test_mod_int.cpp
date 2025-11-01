#include "../../math/mod_int.cpp"
#include <cassert>
#include <iostream>

using namespace std;

int main() {
	constexpr int MOD = 1000000007;
	using mint = ModInt<MOD>;

	// Test 1: Basic construction
	{
		mint a(5);
		assert(int(a) == 5);
		
		mint b(0);
		assert(int(b) == 0);
		
		mint c(MOD);
		assert(int(c) == 0);
		
		mint d(MOD + 5);
		assert(int(d) == 5);
	}

	// Test 2: Negative values
	{
		mint a(-1);
		assert(int(a) == MOD - 1);
		
		mint b(-5);
		assert(int(b) == MOD - 5);
		
		mint c(-MOD);
		assert(int(c) == 0);
	}

	// Test 3: Addition
	{
		mint a(100), b(200);
		mint c = a + b;
		assert(int(c) == 300);
		
		// Test overflow
		mint d(MOD - 10), e(20);
		mint f = d + e;
		assert(int(f) == 10);
	}

	// Test 4: Subtraction
	{
		mint a(200), b(100);
		mint c = a - b;
		assert(int(c) == 100);
		
		// Test underflow
		mint d(10), e(20);
		mint f = d - e;
		assert(int(f) == MOD - 10);
	}

	// Test 5: Multiplication
	{
		mint a(100), b(200);
		mint c = a * b;
		assert(int(c) == 20000);
		
		// Test large multiplication
		mint d(1000000), e(1000000);
		mint f = d * e;
		assert(int(f) == (1LL * 1000000 * 1000000) % MOD);
	}

	// Test 6: Division and inverse
	{
		mint a(10), b(2);
		mint c = a / b;
		assert(int(c) == 5);
		
		// Test inverse directly
		mint d(2);
		mint inv_d = d.inv();
		assert(int(d * inv_d) == 1);
		
		// Test division by checking multiplication
		mint e(15), f(3);
		mint g = e / f;
		assert(int(g * f) == int(e));
	}

	// Test 7: Compound assignment operators
	{
		mint a(10);
		a += mint(5);
		assert(int(a) == 15);
		
		a -= mint(3);
		assert(int(a) == 12);
		
		a *= mint(2);
		assert(int(a) == 24);
		
		a /= mint(4);
		assert(int(a) == 6);
	}

	// Test 8: Power function
	{
		mint a(2);
		mint b = pow(a, 10);
		assert(int(b) == 1024);
		
		mint c(3);
		mint d = pow(c, 0);
		assert(int(d) == 1);
		
		// Large power
		mint e(2);
		mint f = pow(e, 100);
		long long expected = 1;
		for (int i = 0; i < 100; i++) {
			expected = (expected * 2) % MOD;
		}
		assert(int(f) == expected);
	}

	// Test 9: Modular inverse properties
	{
		// For any non-zero a, a * a^(-1) = 1
		for (int val : {1, 2, 3, 5, 7, 100, 12345, 999999}) {
			mint a(val);
			mint inv_a = a.inv();
			mint product = a * inv_a;
			assert(int(product) == 1);
		}
	}

	// Test 10: Equality operator
	{
		mint a(5), b(5), c(6);
		assert(a == b);
		assert(!(a == c));
		
		mint d(MOD + 5);
		assert(a == d);
	}

	// Test 11: Fermat's little theorem
	{
		// a^(MOD-1) = 1 (mod MOD) for prime MOD
		mint a(7);
		mint result = pow(a, MOD - 1);
		assert(int(result) == 1);
	}

	// Test 12: Zero handling
	{
		mint a(5), b(0);
		assert(int(a + b) == 5);
		assert(int(a * b) == 0);
		assert(int(b * a) == 0);
		
		mint c(0);
		assert(int(c) == 0);
	}

	// Test 13: Complex expression
	{
		mint a(2), b(3), c(4);
		mint result = (a + b) * c - a / b;
		
		// (2 + 3) * 4 - 2 / 3
		// = 5 * 4 - 2 * 3^(-1)
		// = 20 - 2 * inv(3)
		mint expected = mint(20) - mint(2) * mint(3).inv();
		assert(int(result) == int(expected));
	}

	// Test 14: Stress test with factorials
	{
		mint fact = 1;
		for (int i = 1; i <= 100; i++) {
			fact *= mint(i);
		}
		
		// Verify by computing inverse
		mint inv_fact = fact.inv();
		assert(int(fact * inv_fact) == 1);
	}

	cout << "All ModInt tests passed!" << endl;
	return 0;
}


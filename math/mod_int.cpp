#include <iostream>
using namespace std;
using ll = long long;

template<class T> T pow(T a, ll b) { T r = 1; for (; b; b /= 2, a *= a) if (b % 2) r *= a; return r; }

// source: ecnerwala, own, Benq
template<int MOD>
struct ModInt {
	int v;
	ModInt() : v(0) {}
	ModInt(ll x) : v(x % MOD) { if (v < 0) v += MOD; }
	explicit operator int() const { return v; }
	explicit operator ll() const { return v; }

	template<class T>
	friend T& operator<<(T& out, const ModInt& a) { return out << int(a); }
	template<class T>
	friend T& operator>>(T& in, ModInt& a) { ll x; in >> x; a = ModInt(x); return in; }

	// only works if MOD is prime
	ModInt inv() const { return pow(*this, MOD - 2); }
	friend ModInt inv(const ModInt& x) { return x.inv(); }

	ModInt& operator+=(const ModInt& a) { v += a.v; if (v >= MOD) v -= MOD; return *this; }
	ModInt& operator-=(const ModInt& a) { v -= a.v; if (v < 0) v += MOD; return *this; }
	ModInt& operator*=(const ModInt& a) { v = ll(v) * ll(a.v) % MOD; return *this; }
	ModInt& operator/=(const ModInt& a) { return *this *= a.inv(); }
	friend ModInt operator+(const ModInt& a, const ModInt& b) { return ModInt(a) += b; }
	friend ModInt operator-(const ModInt& a, const ModInt& b) { return ModInt(a) -= b; }
	friend ModInt operator*(const ModInt& a, const ModInt& b) { return ModInt(a) *= b; }
	friend ModInt operator/(const ModInt& a, const ModInt& b) { return ModInt(a) /= b; }

	bool operator==(const ModInt& oth) { return v == oth.v; }
};

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

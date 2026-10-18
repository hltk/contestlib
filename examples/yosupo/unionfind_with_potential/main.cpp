#include <bits/stdc++.h>

using namespace std;

using ll = long long;

template<class T> T pow(T a, ll b) { T r = 1; for (; b; b /= 2, a *= a) if (b % 2) r *= a; return r; }

// source: ecnerwala, own, Benq
template<int Mod>
struct ModInt {
	int v;
	ModInt() : v(0) {}
	ModInt(ll x) : v(x % Mod) { if (v < 0) v += Mod; }
	explicit operator int() const { return v; }
	explicit operator ll() const { return v; }

	template<class T>
	friend T& operator<<(T& out, const ModInt& a) { return out << int(a); }
	template<class T>
	friend T& operator>>(T& in, ModInt& a) { ll x; in >> x; a = ModInt(x); return in; }

	// only works if Mod is prime
	ModInt inv() const { return pow(*this, Mod - 2); }
	friend ModInt inv(const ModInt& x) { return x.inv(); }

	ModInt& operator+=(const ModInt& a) { v += a.v; if (v >= Mod) v -= Mod; return *this; }
	ModInt& operator-=(const ModInt& a) { v -= a.v; if (v < 0) v += Mod; return *this; }
	ModInt& operator*=(const ModInt& a) { v = ll(v) * ll(a.v) % Mod; return *this; }
	ModInt& operator/=(const ModInt& a) { return *this *= a.inv(); }
	friend ModInt operator+(const ModInt& a, const ModInt& b) { return ModInt(a) += b; }
	friend ModInt operator-(const ModInt& a, const ModInt& b) { return ModInt(a) -= b; }
	friend ModInt operator*(const ModInt& a, const ModInt& b) { return ModInt(a) *= b; }
	friend ModInt operator/(const ModInt& a, const ModInt& b) { return ModInt(a) /= b; }

	bool operator==(const ModInt& oth) const { return v == oth.v; }
};

constexpr int mod = 998'244'353;
using mint = ModInt<mod>;

struct UF {
	UF(int n) : p(n, -1), pot(n) {}
	vector<int> p;
	vector<mint> pot;
	pair<int, mint> root(int x) {
		int ox = x;
		mint r {};
		while (p[x] >= 0) {
			r += pot[x];
			x = p[x];
		}
		return {x, r};
	}
	optional<mint> diff(int x, int y) {
		auto [xi, xp] = root(x);
		auto [yi, yp] = root(y);
		if (xi == yi) {
			return xp - yp;
		}
		return {};
	}
	bool merge(int x, int y, mint d) {
		auto [xi, xp] = root(x);
		auto [yi, yp] = root(y);
		if (xi == yi) {
			return xp - yp == d;
		}
		if (-p[xi] < -p[yi]) {
			pot[xi] = d - xp + yp;
			p[yi] += p[xi];
			p[xi] = yi;
		} else {
			pot[yi] = xp - yp - d;
			p[xi] += p[yi];
			p[yi] = xi;
		}
		return true;
	}
};

int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	UF uf(n);
	for (int qi = 0; qi < q; ++qi) {
		int t, u, v;
		scanf("%d%d%d", &t, &u, &v);
		if (t == 0) {
			int x;
			scanf("%d", &x);
			printf("%d\n", (int)uf.merge(u, v, x));
		} else {
			auto r = uf.diff(u, v);
			if (r) {
				printf("%d\n", (int)*r);
			} else {
				printf("%d\n", -1);
			}
		}
	}
}

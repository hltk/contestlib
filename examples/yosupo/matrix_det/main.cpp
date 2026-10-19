#include <bits/stdc++.h>
#include <cassert>

using namespace std;

using ll = long long;

template<class T> T pow(T a, ll b, T id = 1) { T r = id; for (; b; b /= 2, a *= a) if (b % 2) r *= a; return r; }

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
	friend ModInt operator-(const ModInt& a) { return ModInt(0) -= a; }
	friend ModInt operator*(const ModInt& a, const ModInt& b) { return ModInt(a) *= b; }
	friend ModInt operator/(const ModInt& a, const ModInt& b) { return ModInt(a) /= b; }

	bool operator==(const ModInt& oth) const { return v == oth.v; }
	bool operator<(const ModInt& oth) const { return v < oth.v; }
	bool operator>(const ModInt& oth) const { return v > oth.v; }
	bool operator<=(const ModInt& oth) const { return v <= oth.v; }
	bool operator>=(const ModInt& oth) const { return v >= oth.v; }
};

template <class T>
struct Mat {
	int r, c;
	Mat(int r, int c) : r(r), c(c), m(r, vector<T>(c))  {}

	vector<vector<T>> m;

	using M = Mat<T>;

	static M id(int r, int c) {
		assert(r == c);
		M ret(r, c);
		for (int i = 0; i < r; ++i)
			ret[i][i] = 1;
		return ret;
	}
	M id() { return M::id(r, c); }

	template<class O>
	friend O& operator<<(O& out, const M& a) {
		for (int i = 0; i < a.r; ++i) {
			for (int j = 0; j < a.c; ++j) {
				if (j)
					out << ' ';
				out << a[i][j];
			}
			out << '\n';
		}
		return out;
	}

	M& operator+=(const M& a) {
		assert(a.r == r && a.c == c);
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				m[i * c + j] += a[i][j];
			}
		}
		return *this;
	}
	M& operator-=(const M& a) {
		assert(a.r == r && a.c == c);
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				m[i * c + j] -= a[i][j];
			}
		}
		return *this;
	}
	friend M operator*(const M& a, const M& b) {
		static_assert(a.c == b.r);
		M ret {};
		for (int i = 0; i < a.r; ++i) {
			for (int j = 0; j < b.c; ++j) {
				for (int k = 0; k < a.c; ++k) {
					ret[i][j] += a[i][k] * b[k][j];
				}
			}
		}
		return ret;
	}
	M& operator*=(const M& a) { return (*this = *this * a); }
	friend M operator+(const M& a, const M& b) { return M(a) += b; }
	friend M operator-(const M& a, const M& b) { return M(a) -= b; }
	Mat& operator*=(T t) {
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				m[i * c + j] *= t;
			}
		}
		return *this;
	}
	Mat& operator/=(T t) {
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				m[i * c + j] /= t;
			}
		}
		return *this;
	}
	Mat operator*(T t) { return Mat(*this) *= t; }
	Mat operator/(T t) { return Mat(*this) /= t; }

	bool operator==(const M& b) const { return m == b.m; }

	vector<T>& operator[](int i) {
		return m[i];
	}

};

template <int Mod>
ModInt<Mod> abs(ModInt<Mod> t) { return t; }

// Modified from: https://cp-algorithms.com/linear_algebra/determinant-gauss.html
template <class T>
T det(Mat<T>& a) {
	int n = (int)a.r;
	assert(a.r == a.c);

	T det = 1;
	for (int i = 0; i < n; ++i) {
		int k = i;
		for (int j = i + 1; j < n; ++j)
			if (abs(a[j][i]) > abs(a[k][i]))
				k = j;
		if (abs(a[k][i]) <= 0) {
			det = 0;
			break;
		}
		swap(a[i], a[k]);
		if (i != k)
			det = -det;
		det *= a[i][i];
		for (int j = i + 1; j < n; ++j)
			a[i][j] /= a[i][i];
		for (int j = 0; j < n; ++j)
			if (j != i && abs(a[j][i]) > 0)
				for (int k = i + 1; k < n; ++k)
					a[j][k] -= a[i][k] * a[j][i];
	}
	return det;
}

constexpr int mod = 998'244'353;
using mint = ModInt<mod>;
using mat = Mat<mint>;

int main() {
	int n;
	scanf("%d", &n);

	mat m(n, n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int x;
			scanf("%d", &x);
			m[i][j] = x;
		}
	}

	printf("%d\n", (int)det(m));
}

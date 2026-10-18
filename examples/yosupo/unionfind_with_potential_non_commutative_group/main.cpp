#include <bits/stdc++.h>

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
};

template <int R, int C, class T>
struct Mat {
	array<T, R * C> m;

	using M = Mat<R, C, T>;

	static M id() {
		static_assert(R == C);
		M r{};
		for (int i = 0; i < R; ++i)
			r.m[i * R + i] = 1;
		return r;
	}

	template<class O>
	friend O& operator<<(O& out, const M& a) {
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) {
				if (j)
					out << ' ';
				out << a.m[i * C + j];
			}
			out << '\n';
		}
		return out;
	}

	template<int aR, int aC, class aT>
	Mat& operator+=(const Mat<aR, aC, aT>& a) {
		static_assert(is_same<T, aT>::value);
		static_assert(aR == R && aC == C);
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) {
				m[i * C + j] += a[i * C + j];
			}
		}
		return *this;
	}
	template<int aR, int aC, class aT>
	Mat& operator-=(const Mat<aR, aC, aT>& a) {
		static_assert(is_same<T, aT>::value);
		static_assert(aR == R && aC == C);
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) {
				m[i * C + j] -= a[i * C + j];
			}
		}
		return *this;
	}
	template<int bR, int bC, class bT>
	friend Mat operator*(const M& a, const Mat<bR, bC, bT>& b) {
		static_assert(is_same<T, bT>::value);
		static_assert(C == bR);
		Mat<R, bC, T> ret {};
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < bC; ++j) {
				for (int k = 0; k < C; ++k) {
					ret.m[i * bC + j] += a[i * C + k] * b[k * bC + j];
				}
			}
		}
		return ret;
	}
	template<int aR, int aC, class aT>
	M& operator*=(const Mat<aR, aC, aT>& a) { return (*this = *this * a); }
	template <int bR, int bC, class bT>
	friend Mat operator+(const M& a, const Mat<bR, bC, bT>& b) { return M(a) += b; }
	template <int bR, int bC, class bT>
	friend Mat operator-(const M& a, const Mat<bR, bC, bT>& b) { return M(a) -= b; }
	Mat& operator*=(T t) {
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) {
				m[i * C + j] *= t;
			}
		}
		return *this;
	}
	Mat& operator/=(T t) {
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) {
				m[i * C + j] /= t;
			}
		}
		return *this;
	}
	Mat operator*(T t) { return Mat(*this) *= t; }
	Mat operator/(T t) { return Mat(*this) /= t; }

	template <int bR, int bC, class bT>
	bool operator==(const Mat<bR, bC, bT>& b) const { return R == bR && C == bC && m == b.m; }

	T operator[](int i) const { return m[i]; }

	M inv() const {
		static_assert(R == 2 && C == 2);
		auto a = m[0];
		auto b = m[1];
		auto c = m[2];
		auto d = m[3];
		return M {d, -b, -c, a} / (a * d - b * c);
	}
};

constexpr int mod = 998'244'353;
using mint = ModInt<mod>;
using mat = Mat<2, 2, mint>;

struct UF {
	UF(int n) : p(n, -1), pot(n) {}
	vector<int> p;
	vector<mat> pot;
	pair<int, mat> root(int x) {
		int ox = x;
		mat r = mat::id();
		while (p[x] >= 0) {
			r = pot[x] * r;
			x = p[x];
		}
		return {x, r};
	}
	optional<mat> diff(int x, int y) {
		auto [xi, xp] = root(x);
		auto [yi, yp] = root(y);

		if (xi == yi) {
			return yp.inv() * xp;
		}
		return {};
	}
	bool merge(int x, int y, mat d) {
		auto [xi, xp] = root(x);
		auto [yi, yp] = root(y);
		if (xi == yi) {
			return yp.inv() * xp == d;
		}
		if (-p[xi] < -p[yi]) {
			p[yi] += p[xi];
			pot[xi] = (xp * d.inv() * yp.inv()).inv();
			p[xi] = yi;
		} else {
			p[xi] += p[yi];
			pot[yi] = xp * d.inv() * yp.inv();
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
			int x1, x2, x3, x4;
			scanf("%d%d%d%d", &x1, &x2, &x3, &x4);
			mat x {{x1, x2, x3, x4}};
			printf("%d\n", (int)uf.merge(u, v, x));
		} else {
			auto r = uf.diff(u, v);
			if (r) {
				auto rx = *r;
				printf("%d %d %d %d\n", (int)rx[0], (int)rx[1], (int)rx[2], (int)rx[3]);
			} else {
				printf("%d\n", -1);
			}
		}
	}
}

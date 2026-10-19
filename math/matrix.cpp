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
				m[i][j] += a[i][j];
			}
		}
		return *this;
	}
	M& operator-=(const M& a) {
		assert(a.r == r && a.c == c);
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				m[i][j] -= a[i][j];
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

	const vector<T>& operator[](int i) const { return m[i]; }
	vector<T>& operator[](int i) { return m[i]; }
};

constexpr int mod = 998'244'353;
using mat = Mat<mint>;

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

	T& operator[](int i) const { return m[i]; }

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

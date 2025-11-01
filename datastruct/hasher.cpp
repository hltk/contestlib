#include <chrono>
#include <random>
#include <tuple>
#include <vector>
using namespace std;

#include "../math/mod_int.cpp"

namespace hasher {
	const int MOD = 1e9 + 7;
	using hash_t = ModInt<MOD>;

	class HashPair {
		hash_t x, y;

	public:
		HashPair() : x(0), y(0) {}
		HashPair(hash_t u) : x(u), y(u) {}
		HashPair(hash_t x, hash_t y) : x(x), y(y) {}

		HashPair& operator*=(const HashPair& oth) {
			x *= oth.x;
			y *= oth.y;
			return *this;
		}
		HashPair& operator+=(const HashPair& oth) {
			x += oth.x;
			y += oth.y;
			return *this;
		}
		HashPair& operator-=(const HashPair& oth) {
			x -= oth.x;
			y -= oth.y;
			return *this;
		}
		friend HashPair operator*(const HashPair& lhs, const HashPair& rhs) { return HashPair(lhs) *= rhs; }
		friend HashPair operator+(const HashPair& lhs, const HashPair& rhs) { return HashPair(lhs) += rhs; }
		friend HashPair operator-(const HashPair& lhs, const HashPair& rhs) { return HashPair(lhs) -= rhs; }
		bool operator==(const HashPair& oth) { return tie(x, y) == tie(oth.x, oth.y); }
		bool operator!=(const HashPair& oth) { return !((*this) == oth); }
	};

	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	auto dist = uniform_int_distribution<int>(MOD * 0.1, MOD * 0.9);

	HashPair bases(hash_t(dist(rng)), hash_t(dist(rng)));

	template<class T>
	HashPair calc(const T& x) {
		HashPair r;
		for (auto& u : x) r = r * bases + HashPair(hash_t(u));
		return r;
	}

	template<class T>
	vector<HashPair> calc_vector(const T& x) {
		vector<HashPair> r(1);
		for (auto& u : x) r.push_back(r.back() * bases + HashPair(hash_t(u)));
		return r;
	}

	vector<HashPair> pows {bases};

	void ensure_pows(int n) {
		if (int(pows.size()) >= n) return;
		while (int(pows.size()) < n) pows.push_back(pows.back() * bases);
	}

	HashPair range(const vector<HashPair>& k, int l, int r) { // [l, r)
		ensure_pows(r - l);
		return k[r] - k[l] * pows[r - l - 1];
	}
} // namespace hasher

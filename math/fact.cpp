#include <vector>
using namespace std;

#include "mod_int.cpp"

namespace comb {
	vector<mint> fact, ifact;

	void ensure_facts(int n) {
		if (int(fact.size()) >= n) return;
		if (fact.empty()) {
			fact.emplace_back(1);
			ifact.emplace_back(1);
		}
		while (int(fact.size()) < n) {
			fact.push_back(fact.back() * fact.size());
			ifact.push_back(1 / fact.back());
		}
	}

	mint choose(int a, int b) {
		if (a < b || b < 0) return 0;
		ensure_facts(a);
		return fact[a] * ifact[b] * ifact[a - b];
	}

	mint factorial(int a) {
		ensure_facts(a);
		return fact[a];
	}

	mint inv_factorial(int a) {
		ensure_facts(a);
		return ifact[a];
	}
} // namespace comb

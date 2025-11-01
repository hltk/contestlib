#include <chrono>
#include <random>
#include <tuple>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// source: cses.fi/ioi16/list, cses.fi/alon20/list, mango_lassi
struct Treap {
	template<class T>
	int rand() {
		return uniform_int_distribution<T>()(rng);
	}

	Treap *l, *r;
	int prior, sz, v;

	void push() {}

	void update() {
		sz = 1 + (l != nullptr ? l->sz : 0) + (r != nullptr ? r->sz : 0);
	}

	Treap(int v_) : l(0), r(0), prior(rand<int>()), sz(1), v(v_) {}
	static Treap* merge(Treap* a, Treap* b) {
		if (a != nullptr) {
			a->push();
		}
		if (b != nullptr) {
			b->push();
		}
		if ((a == nullptr) || (b == nullptr)) {
			return (a != nullptr ? a : b);
		}

		Treap* r;
		if (a->prior < b->prior) {
			if (a->r != nullptr) {
				a->r->push();
			}
			a->r = merge(a->r, b);
			r = a;
		} else {
			if (b->l != nullptr) {
				b->l->push();
			}
			b->l = merge(a, b->l);
			r = b;
		}
		r->update();
		return r;
	}

	static pair<Treap*, Treap*> split(Treap* a, int k) {
		if (a == nullptr) {
			return {0, 0};
		}
		a->push();
		int al = a->l != nullptr ? a->l->sz : 0;
		Treap* r;
		if (al >= k) {
			tie(r, a->l) = split(a->l, k);
			a->update();
			return {r, a};
		}
		tie(a->r, r) = split(a->r, k - al - 1);
		a->update();
		return {a, r};
	}
};

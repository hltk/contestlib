#include <functional>
#include <vector>
using namespace std;

// Basic segment tree. Takes the size of tree, an identity value
// and a binary function as parameters
template<class T>
class Tree {
	int n; // Has to be a power of 2
	T I;
	function<T(T, T)> f;
	vector<T> t;

public:
	Tree(int n, T I, function<T(T, T)> f) : n(n), I(I), f(f), t(n * 2, I) {}

	void change(int k, T x) {
		k += n;
		t[k] = x;
		while (k /= 2) t[k] = f(t[k * 2], t[k * 2 + 1]);
	}
	T query(int a, int b) { // [a, b)
		T r = I;
		static T buf[128];
		int bufit = 0;
		for (a += n, b += n; a < b; a /= 2, b /= 2) {
			if (a & 1) r = f(r, t[a++]);
			if (b & 1) buf[bufit++] = t[--b];
		}
		for (int i = bufit - 1; i >= 0; --i) r = f(r, buf[i]);
		return r;
	}
};

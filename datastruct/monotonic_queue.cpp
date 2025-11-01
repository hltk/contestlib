#include <deque>
using namespace std;

template<class T, class Compare>
class MonotonicQueue {
	int l = 0, r = 0;
	deque<pair<T, int>> d;

public:
	void push(T x) {
		while (!d.empty() && !Compare()(d.back().first, x)) {
			d.pop_back();
		}
		d.push_back({x, r++});
	}
	void pop() {
		if (d.front().second == l++) d.pop_front();
	}
	T get() { return d.front().first; }
};

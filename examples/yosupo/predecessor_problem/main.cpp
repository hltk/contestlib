#include <bits/stdc++.h>

using namespace std;

const int N = 1e7;
char state[N + 1];

int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	scanf("%s", state);
	set<int> s;
	for (int i = 0; i < n; ++i)
		if (state[i] == '1')
			s.insert(i);
	for (int qi = 0; qi < q; ++qi) {
		int c, k;
		scanf("%d%d", &c, &k);
		if (c == 0) {
			s.insert(k);
		} else if (c == 1) {
			auto it = s.find(k);
			if (it != s.end())
				s.erase(it);
		} else if (c == 2) {
			printf("%d\n", s.find(k) != s.end());
		} else if (c == 3) {
			auto it = s.lower_bound(k);
			printf("%d\n", it == s.end() ? -1 : *it);
		} else if (c == 4) {
			auto it = s.upper_bound(k);
			printf("%d\n", it == s.begin() ? -1 : *prev(it));
		}
	}
}

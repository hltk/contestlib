#include <bits/stdc++.h>

using namespace std;

int main() {
	int q;
	scanf("%d", &q);

	map<long, long> m;

	for (int qi = 0; qi < q; ++qi) {
		int t;
		long k, v;
		scanf("%d%ld", &t, &k);
		if (t == 0) {
			scanf("%ld", &v);
			m[k] = v;
		} else {
			printf("%ld\n", m[k]);
		}
	}
}

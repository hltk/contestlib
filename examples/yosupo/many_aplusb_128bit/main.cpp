#include <bits/stdc++.h>

using namespace std;

int main() {
	int t;
	cin >> t;
	for (int ti = 0; ti < t; ++ti) {
		string as, bs;
		cin >> as >> bs;
		__int128_t a {}, b {};
		bool aneg {}, bneg {};
		if (as[0] == '-') {
			aneg = true;
			as = as.substr(1);
		}
		if (bs[0] == '-') {
			bneg = true;
			bs = bs.substr(1);
		}
		for (char c : as)
			a = a * 10 + c - '0';
		for (char c : bs)
			b = b * 10 + c - '0';
		a *= aneg ? -1 : 1;
		b *= bneg ? -1 : 1;
		string ans;
		auto sum = a + b;
		bool sumneg {};
		if (sum < 0) {
			sumneg = true;
			sum = -sum;
		}
		if (sum == 0) ans = "0";
		while (sum) {
			ans.push_back(sum % 10 + '0');
			sum /= 10;
		}
		if (sumneg) ans.push_back('-');
		cout << string{ans.rbegin(), ans.rend()} << '\n';
	}
}

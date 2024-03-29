// Finds the partition point of f in range [l, r],
// i.e. minimum x such that f(x) = true.
// Never evaluates f(r).
auto bins = [](auto l, auto r, auto f) {
	while (l < r) {
		auto m = l + (r - l) / 2;
		if (f(m)) r = m;
		else l = m + 1;
	}
	return l;
};

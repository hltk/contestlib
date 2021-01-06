// source: Benq

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <typename T>
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; 

// Use with pairs to get a multiset
// Useful functions:
// 	tree.order_of_key
// 	tree.find_by_order

template<typename T>
int at_most(indexed_set<pair<T, int>>& t, T k) {
	return tree.order_of_key({k, INF});
}

template<typename T>
int at_least(indexed_set<pair<T, int>>& t, T k) {
	return tree.size() - at_most(t, k - 1);
}

template<typename T>
int range_sum(indexed_set<pair<T, int>>& t, T l, T r) {
	return at_most(r) - at_most(l - 1);
}

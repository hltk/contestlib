#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct LCA {
	int n;
	int B;
	int m; 
	vector<int> depth;
	vector<int> position;
	vector<int> tour;
	vector<int> block_id;
	vector<int> block_min;
	vector<vector<int>> block_sparse;
	vector<vector<vector<int>>> blocks;

	void dfs(int node, int parent, vector<vector<int>> &g) {
		tour.push_back(node);
		for (int child : g[node]) {
			if (child == parent) continue;
			depth[child] = depth[node] + 1;
			dfs(child, node, g);
			tour.push_back(node);
		}
	}


	int block_sparse_query(int l, int r) {
		int lvl = __lg(r - l + 1);
		int a = block_sparse[lvl][l];
		int b = block_sparse[lvl][r - (1 << lvl) + 1];
		return depth[a] < depth[b] ? a : b;
	}

	LCA(vector<vector<int>> &g, int root = 0) : n(int(size(g))),
					B(max(1, __lg(n) / 2)),
					m((2 * n - 1) / B),
					depth(n),
					position(n, -1),
					block_id(m),
					block_min(m),
					blocks(1 << (B - 1), vector<vector<int>>(B, vector<int>(B))) {
		auto compare_depth = [&](int a, int b) {
			return depth[a] < depth[b];
		};

		tour.reserve(n + n - 1);
		dfs(root, root, g);

		for (int i = 0, j = 0; j < m; i += B, ++j) {
			block_min[j] = *min_element(tour.begin() + i, tour.begin() + min(2 * n - 1, i + B), compare_depth);
			for (int k = 0; k < B - 1; ++k) {
				int diff = i + k + 1 < 2 * n - 1 ? depth[tour[i + k + 1]] - depth[tour[i + k]] : 1;
				block_id[j] += (1 << k) * (diff == 1);
			}
		}

		block_sparse.push_back(block_min);
		for (int j = 0; (2 << j) <= m; ++j) {
			block_sparse.emplace_back(m - (1 << j));
			for (int i = 0; i + (2 << j) <= m; ++i) {
				int a = block_sparse[j][i];
				int b = block_sparse[j][i + (1 << j)];
				block_sparse[j + 1][i] = min(a, b, compare_depth);
			}
		}

		for (auto &i : tour) {
			if (position[i] < 0) {
				position[i] = (int) (&i - tour.data());
			}
		}

		vector<int> block(B);
		for (int j = 0; j < (1 << (B - 1)); ++j) {
			for (int i = 0; i < B - 1; ++i) {
				block[i + 1] = block[i] + (j >> i & 1 ? +1 : -1);
			}
			for (int l = 0; l < B; ++l) {
				int min_node = l;
				for (int r = l; r < B; ++r) {
					if (block[r] < block[min_node]) {
						min_node = r;
					}
					blocks[j][l][r] = min_node;
				}
			}
		}
	}

	int query(int a, int b) {
		a = position[a];
		b = position[b];
		if (b < a) swap(a, b);

		int ans = tour[a];

		auto offer = [&](int node) {
			if (depth[node] < depth[ans]) ans = node;
		};

		int a_block = a / B;
		int b_block = b / B;

		if (a_block + 1 <= b_block - 1) {
			offer(block_sparse_query(a_block + 1, b_block - 1));
		}

		if (a_block == b_block) {
			offer(tour[a_block * B + blocks[block_id[a_block]][a % B][b % B]]);
		} else {
			offer(tour[a_block * B + blocks[block_id[a_block]][a % B][B - 1]]);
			offer(tour[b_block * B + blocks[block_id[b_block]][0][b % B]]);
		}

		return ans;
	}
};

struct RMQ {
	vector<vector<int>> g;
	int root;
	LCA lca;

	int cartesian_tree(vector<int> &v) {
		const int n = (int) v.size();
		vector<int> parent(n, -1);
		vector<int> stack;
		for (int i = 0; i < n; ++i) {
			int last = -1;
			while (!stack.empty() && v[stack.back()] >= v[i]) {
				last = stack.back();
				stack.pop_back();
			}
			if (last != -1) parent[last] = i;
			if (!stack.empty()) parent[i] = stack.back();
			stack.push_back(i);
		}

		for (int i = 0; i < n; ++i) {
			if (parent[i] >= 0) g[parent[i]].push_back(i);
		}
		return (int) (find(parent.begin(), parent.end(), -1) - parent.begin());
	}

	RMQ(vector<int> &v) : g(v.size()), root(cartesian_tree(v)), lca(g, root) {}

	int query(int a, int b) {
		return lca.query(a, b);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, q;
	cin >> n >> q;

	vector<int> v(n);
	for (int &x : v) {
		cin >> x;
	}

	RMQ rmq(v);

	while (q--) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		cout << v[rmq.query(a, b)] << '\n';
	}
}

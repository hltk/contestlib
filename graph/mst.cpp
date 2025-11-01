#include <algorithm>
#include <vector>
#include "../datastruct/dsu.cpp"
using namespace std;
using ll = long long;

// Kruskal's Minimum Spanning Tree algorithm
// O(E log E) time complexity (mainly from sorting edges)
template<typename T = ll>
struct MST {
	struct Edge {
		int u, v;
		T w;
		bool operator<(const Edge& e) const { return w < e.w; }
	};

	vector<Edge> edges;
	int n;

	MST(int n) : n(n) {}

	void addedge(int u, int v, T w, bool /* directed */ = false) {
		edges.push_back({u, v, w});
		// For undirected graphs, only one edge needed (Kruskal processes both directions)
	}

	// Run Kruskal's algorithm, returns MST weight and edges
	// Returns {total_weight, mst_edges}
	// If graph is disconnected, returns weight of spanning forest
	pair<T, vector<Edge>> run() {
		sort(edges.begin(), edges.end());

		DSU dsu(n);
		T total_weight = 0;
		vector<Edge> mst_edges;

		for (const auto& e : edges) {
			if (!dsu.same(e.u, e.v)) {
				dsu.merge(e.u, e.v);
				total_weight += e.w;
				mst_edges.push_back(e);
			}
		}

		return {total_weight, mst_edges};
	}

	// Get MST weight only
	T get_weight() {
		auto [weight, _] = run();
		return weight;
	}

	// Get MST edges only
	vector<Edge> get_edges() {
		auto [_, edges] = run();
		return edges;
	}
};


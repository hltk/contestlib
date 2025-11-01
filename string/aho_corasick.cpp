template<char MC = 'a', int AS = 26>
class AhoCorasick {
	class Node {
	public:
		int nxt[AS];
		int link = 0; // suffix link to the next true suffix that appears in the tree
		int dict = -1; // suffix link to the next true suffix that appears in the dictionary
		int word_index = -1;
		Node() {
			fill(nxt, nxt + AS, -1);
		}
	};
	vector<Node> nodes;
	int add_word(string& s) {
		int n = 0;
		for (auto c : s) {
			c -= MC;
			if (nodes[n].nxt[c] < 0) {
				nodes[n].nxt[c] = nodes.size();
				nodes.emplace_back();
			}
			n = nodes[n].nxt[c];
		}
		return n;
	}
	vector<int> word_index;
	vector<int> sorted_word_indices;
	vector<int> rev;
public:
	AhoCorasick(vector<string>& words) : nodes(1), word_index(words.size()), rev(words.size()) {
		for (int i = 0; i < (int)words.size(); ++i) {
			word_index[i] = add_word(words[i]);
			int& j = nodes[word_index[i]].word_index;
			if (j < 0) j = i;
			rev[i] = j;
		}
		queue<int> que;
		que.push(0);
		while (!que.empty()) {
			int n = que.front();
			que.pop();
			if (nodes[n].word_index >= 0) {
				sorted_word_indices.push_back(n);
			}
			int k = nodes[n].link;
			for (int i = 0; i < AS; ++i) {
				if (nodes[n].nxt[i] < 0) {
					nodes[n].nxt[i] = max(nodes[k].nxt[i], 0);
				}
				else {
					int u = n ? nodes[k].nxt[i] : 0;
					nodes[nodes[n].nxt[i]].link = u;
					nodes[nodes[n].nxt[i]].dict = nodes[u].word_index < 0 ? nodes[u].dict : u;
					que.push(nodes[n].nxt[i]);
				}
			}
		}
		reverse(sorted_word_indices.begin(), sorted_word_indices.end());
	}
	vector<int> match(string& s) {
		vector<int> ret(word_index.size());
		int n = 0;
		for (auto c : s) {
			n = nodes[n].nxt[c - MC];
			if (int d = nodes[n].word_index < 0 ? nodes[n].dict : n; d >= 0) {
				ret[nodes[d].word_index]++;
			}
		}
		for (auto i : sorted_word_indices) {
			if (int d = nodes[i].dict; d >= 0) {
				ret[nodes[d].word_index] += ret[nodes[i].word_index];
			}
		}
		for (int i = 0; i < (int)ret.size(); ++i) ret[i] = ret[rev[i]];
		return ret;
	}
};

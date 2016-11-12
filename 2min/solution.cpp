#include <bits/stdc++.h>

using namespace std;

class FenwickTree {
public:
	FenwickTree(int n) {
		tree = vector<int>(n, 0);
	}
	
	int query(int x) {
		int ret = 0;
		while (x) {
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}

	int query(int l, int r) {
		return query(r) - query(l - 1);
	}
	
	void update(int x, int v) {
		for (int i = x; i < tree.size(); i += i & -i) {
			tree[i] += v;
		}
	}

private:
	vector<int> tree;
};

class Range {
public:
	Range() { }
	Range(int x, int y, int i)
		: m_x(x)
		, m_y(y)
		, m_i(i)
	{
	}

	int getX() const { return m_x; }
	int getY() const { return m_y; }
	int getI() const { return m_i; }

	bool operator < (const Range& other) const {
		return (m_y == other.m_y) ? (m_i < other.m_i) : (m_y < other.m_y);
	}

private:
	int m_x;
	int m_y;
	int m_i;
};

int main() {
	ios::sync_with_stdio(false);
	int n, x;
	cin >> n;
	vector<Range> intervals;
	stack<pair<int, int> > st;
	for (int i = 0; i < n; ++i) {
		cin >> x;
		while (!st.empty()) {
			pair<int, int> u = st.top();
			intervals.push_back(Range(u.second, i + 1, -1));
			if (u.first > x) {
				st.pop();
			} else break;
		}
		st.push({x, i + 1});
	}
	int q, l, r;
	cin >> q;
	vector<int> ans(q);
	for (int i = 0; i < q; ++i) {
		cin >> l >> r;
		intervals.push_back(Range(l, r, i));
	}
	sort(intervals.begin(), intervals.end());
	FenwickTree ft = FenwickTree(n);
	for (const Range& r : intervals) {
		if (r.getI() < 0) {
			ft.update(r.getX(), 1);
		} else {
			ans[r.getI()] = ft.query(r.getX(), r.getY());
		}
	}
	for (int i = 0; i < q; ++i) {
		cout << ans[i] << '\n';
	}
	return 0;
}

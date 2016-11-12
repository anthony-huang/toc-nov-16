#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, q, l, r;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	cin >> q;
	for (int i = 0; i < q; ++i) {
		cin >> l >> r;
		--l, --r;
		stack<int> st;
		int ans = 0;
		for (int j = l; j <= r; ++j) {
			while (!st.empty()) {
				int u = st.top();
				++ans;
				if (u > a[j]) {
					st.pop();
				} else break;
			}
			st.push(a[j]);
		}
		cout << ans << '\n';
	}
	return 0;
}

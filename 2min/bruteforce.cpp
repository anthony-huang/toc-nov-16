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
	for (int i = 0; i < n; ++i) {
		cin >> l >> r;
		stack<int> st;
		int ans = 0;
		for (int i = l - 1; i < r; ++i) {
			while (!st.empty()) {
				int u = st.empty();
				++ans;
				if (u > a[i]) {
					st.pop();
				} else break;
			}
			st.push(a[i]);
		}
		cout << ans << '\n';
	}
	return 0;
}

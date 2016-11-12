#include <bits/stdc++.h>

using namespace std;

int n,daging,telur,kenyang_saitama,kenyang_genos;
string s;

int main() {
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) {
		if (kenyang_saitama > kenyang_genos) {
			printf("%d GENOS\n",i);
			fflush(stdout);
			
			cin >> s;
			if (s == "SAITAMA") {
				daging++;
			} else {
				// s == "SERI"
				telur++;
				kenyang_genos++;
			}
		} else {
			// kenyang_saitama == kenyang_genos
			printf("%d SAITAMA\n",i);
			fflush(stdout);
			
			cin >> s;
			if (s == "SAITAMA") {
				daging++;
				kenyang_saitama++;
			} else {
				// s == "SERI"
				telur++;
			}
		}
	}
	printf("%d %d\n",daging,telur);
	fflush(stdout);
}
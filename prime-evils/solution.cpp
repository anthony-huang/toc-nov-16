#include <bits/stdc++.h>

using namespace std;

int n,ans;
int a[100007];
long long k;
bool isPrime[1000007];
vector<int> prime_evils,normal_evils;

int main() {
	for (int i = 2; i <= 1000000; i++) isPrime[i] = true;
	for (int i = 2; i <= 1000; i++) if (isPrime[i]) {
		int j = i * i;
		while (j <= 1000000) {
			isPrime[j] = false;
			j += i;
		}
	}

	scanf("%d%lld",&n,&k);
	for (int i = 0; i < n; i++) scanf("%d",&a[i]);
	
	sort(a,a+n);
	for (int i = 0; i < n; i++) {
		if (isPrime[a[i]]) prime_evils.push_back(a[i]);
		else normal_evils.push_back(a[i]);
	}
	
	for (int i = 0; i < normal_evils.size(); i++) {
		if (normal_evils[i] <= k) {
			ans++;
			k -= normal_evils[i];
		}
	}
	
	if (!prime_evils.empty() && prime_evils[0] <= k) ans++;
	if (ans == n) printf("One Punch!\n"); else printf("%d\n",ans);
}
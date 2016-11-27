#include <bits/stdc++.h>

#define __INIT_CC__ ios::sync_with_stdio(false); \
	cin.tie(0);

#ifdef __WIN32__
	char getchar_unlocked() {return getchar();}
#endif

#define FOR(_i,_n,_m) for(int (_i)=(_n),_t=(_m);_i<(_t);++(_i))
#define FORN(_i,_n,_m) for(int (_i)=(_n),_t=(_m);_i<=(_t);++(_i))
#define FORD(_i,_n,_m) for(int (_i)=(_n),_t=(_m);_i>=(_t);--(_i))
#define FORLL(_i,_n,_m) for(long long (_i)=(_n),_t=(_m);_i<(_t);++(_i))
#define FORNLL(_i,_n,_m) for(long long (_i)=(_n),_t=(_m);(_i)<=(_t);++(_i))
#define FORDLL(_i,_n,_m) for(long long (_i)=(_n),_t=(_m);(_i)>=(_t);--(_i))
#define FOREACH(_i,_a) for (__typeof(_a.begin()) _i=_a.begin();_i!=_a.end();++_i)
#define RESET(_a,_value) memset(_a,_value,sizeof(_a))
#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define ff first
#define ss second
#define mp make_pair
#define SIZE(_a) (int)_a.size()
#define VSORT(_a) sort(_a.begin(),_a.end())
#define SSORT(_a,_val) sort(_a,_a+(_val))
#define ALL(_a) _a.begin(),_a.end()
#define mt make_tuple
#define _get(_tuple,_i) get<_i>(_tuple)
#define eb emplace_back
 
using namespace std;
 
const int dr[] = { 1, 0,-1, 0, 1, 1,-1,-1};
const int dc[] = { 0, 1, 0,-1, 1,-1,-1, 1};
const double eps = 1e-9;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pll;
typedef vector<pll> vpll;
typedef vector<ll> vll;
typedef pair<double,double> pdd;
typedef vector<pdd> vpdd;
const int INF = 0x7FFFFFFF;
const ll INFLL = 0x7FFFFFFFFFFFFFFFLL;
const double pi = acos(-1);

template <class T> T take(queue<T> &O) {T tmp=O.front();O.pop();return tmp;}
template <class T> T take(stack<T> &O) {T tmp=O.top();O.pop();return tmp;}
template <class T> T take(priority_queue<T> &O) {T tmp=O.top();O.pop();return tmp;}
template <class T> inline void getint(T &num)
{
	bool neg = 0;
	num = 0;
	char c;
	while ((c = getchar_unlocked()) && (!isdigit(c) && c != '-'));
	if (c == '-')
	{
		neg = 1;
		c = getchar_unlocked();
	}
	do num = num * 10 + c - '0';
	while ((c = getchar_unlocked()) && isdigit(c));
	if (neg) num = -num;
}

template <class T> inline bool inRange(T z, T a, T b){return a <= z && z <= b;}

void OPEN(string in = "input.txt",string out = "output.txt")
{
	freopen(in.c_str(), "r", stdin);
	freopen(out.c_str(), "w", stdout);
	return ;
}

//using sokokaleb's template v3.1

const int MOD = 1000000009;
const int BASE = 63;
const int BAGI_BASE = 984126993;
#define MAXLEN 1000005

string s;
int _hash[MAXLEN]; // _hash[i] stores s[0..i]
const string SIGMA = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
int mapping[256];
int _stack[MAXLEN], sz_stack;
int bagi_base[MAXLEN]; // bagi_base[i] = BASE^(-i)

int take_hash(int l, int len) {
	int r = l + len - 1;
	if (l == 0) {
		return _hash[r];
	}
	int tmp = _hash[r] - _hash[l - 1];
	if (tmp < 0) tmp += MOD;
	tmp = (1LL * tmp * bagi_base[l]) % MOD;
	return tmp;
}

int main(int argc, char** argv) {
	__INIT_CC__

	FOR (i, 0, SIZE(SIGMA)) {
		mapping[SIGMA[i]] = i + 1;
	}
	bagi_base[0] = 1;
	FOR (i, 1, MAXLEN) {
		bagi_base[i] = (1LL * bagi_base[i - 1] * BAGI_BASE) % MOD;
	}

	cin >> s;
	int pkt = 1;
	FOR (i, 0, SIZE(s)) {
		_hash[i] = (1LL * pkt * mapping[s[i]]) % MOD;
		if (i > 0) {
			_hash[i] += _hash[i - 1];
			if (_hash[i] >= MOD) _hash[i] -= MOD;
		}
		pkt = (1LL * pkt * BASE) % MOD;
	}

	_stack[sz_stack++] = 0;
	int longest = 0;
	FOR (i, 1, SIZE(s)) {
		_stack[sz_stack++] = i;
		int length = 1;
		while (sz_stack - 1 != longest
				&& take_hash(_stack[sz_stack - 1], length) != take_hash(_stack[longest], length)) {
			--sz_stack;
			length = min(_stack[longest + 1] - _stack[longest], i - _stack[sz_stack - 1] + 1);
		}
		if (i - _stack[sz_stack - 1] + 1 > _stack[longest + 1] - _stack[longest]) {
			longest = sz_stack - 1;
		}
	}

	cout << sz_stack << "\n";
	FOR (i, 0, sz_stack) {
		if (i) cout << " ";
		cout << _stack[i] + 1;
	}
	cout << "\n";
	return 0;
}

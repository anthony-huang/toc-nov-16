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

void AC() {
	cout << "AC\n";
	exit(0);
}

void WA() {
	cout << "WA\n";
	exit(0);
}

string s;
vector<int> vec;
int judge_ans, contestant_ans;

const int MOD = 1000000009;
const int BASE = 63;
const int BAGI_BASE = 984126993;
#define MAXLEN 1000005
int _hash[MAXLEN];
const string SIGMA = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
int mapping[256];
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
	ifstream tc_in(argv[1]);
	ifstream jud_ans(argv[2]);
	ifstream con_ans(argv[3]);

	tc_in >> s;

	jud_ans >> judge_ans;

	con_ans >> contestant_ans;
	if (con_ans.rdstate())
		WA();

	if (judge_ans != contestant_ans)
		WA();

	for (int i = 0; i < judge_ans; ++i) {
		int tmp;
		con_ans >> tmp;
		--tmp;
		if (con_ans.rdstate())
			WA();
		vec.push_back(tmp);
	}
	string tmp;
	con_ans >> tmp;
	if (!con_ans.rdstate())
		WA();

	vec.push_back(s.length());
	for (int i = 1; i < vec.size(); ++i) {
		if (vec[i - 1] >= vec[i])
			WA();
	}

	for (int i = 0; i < SIGMA.length(); ++i) {
		mapping[SIGMA[i]] = i + 1;
	}
	bagi_base[0] = 1;
	for (int i = 1; i < MAXLEN; ++i) {
		bagi_base[i] = (1LL * bagi_base[i - 1] * BAGI_BASE) % MOD;
	}

	int pkt = 1;
	for (int i = 0; i < s.length(); ++i) {
		_hash[i] = (1LL * pkt * mapping[s[i]]) % MOD;
		if (i > 0) {
			_hash[i] += _hash[i - 1];
			if (_hash[i] >= MOD) _hash[i] -= MOD;
		}
		pkt = (1LL * pkt * BASE) % MOD;
	}

	int longest = 0;
	int L;
	for (int i = 0; i < judge_ans; ++i) {
		if (vec[i + 1] - vec[i] > longest) {
			longest = vec[i + 1] - vec[i];
			L = vec[i];
		}
	}

	for (int i = 0; i < judge_ans; ++i) {
		int len = min(longest, vec[i + 1] - vec[i]);
		if (take_hash(vec[i], len) != take_hash(L, len))
			WA();
	}

	AC();
	return 0;
}

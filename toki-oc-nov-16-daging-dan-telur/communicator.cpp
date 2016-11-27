#include <bits/stdc++.h>
using namespace std;

int wa() {
	cerr << "WA" << endl;
	return 0;
}

int ac() {
	cerr << "AC" << endl;
	return 0;
}

int N, daging, telur, kenyang_saitama, kenyang_genos, A[107];
bool flag[107];

int main(int argc, char* argv[]) {
	ifstream tc_in(argv[1]);
	
	tc_in >> N;
	for (int i = 1; i <= N; i++) {
		tc_in >> A[i];
		if (A[i] == 0) telur++; else daging++;
	}
	cout << N << endl;
	
	int food;
	int dish_left = N;
	string hero;
	
	while (dish_left > 0 && cin >> food >> hero) {
		if (food < 1 || food > N || (hero != "SAITAMA" && hero != "GENOS")) return wa();
		if (flag[food]) return wa();
		
		flag[food] = true;
		dish_left--;
		
		if (A[food] == 1 && hero == "SAITAMA") kenyang_saitama++;
		if (A[food] == 0 && hero == "GENOS") kenyang_genos++;
		
		if (kenyang_saitama >  kenyang_genos) cout << "SAITAMA" << endl;
		if (kenyang_saitama == kenyang_genos) cout << "SERI" << endl;
		if (kenyang_saitama <  kenyang_genos) cout << "GENOS" << endl;
	}
	
	if (dish_left > 0) return wa();
	
	int tebak_daging, tebak_telur;
	if (cin >> tebak_daging >> tebak_telur) {
		if (tebak_daging == daging && tebak_telur == telur) return ac();
		else return wa();
	} else return wa();
}

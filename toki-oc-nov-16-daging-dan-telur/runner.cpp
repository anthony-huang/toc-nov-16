#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class Problem : public BaseProblem {
protected:
	int N;
	vector<int> A;

	void InputFormat() {
		LINE(N);
		LINE(A % SIZE(N));
	}

	void OutputFormat() {
		
	}

	void Subtask1() {
		CONS(1 <= N && N <= 100);
		CONS(inRange(A, 0, 1));
		CONS(A.size() == N);
	}
	
	bool inRange(vector<int>& V, int L, int R){
    	for(int i : V)
			if(i < L || R < i)
				return false;
    	return true;
	}
};

class Generator : public BaseGenerator<Problem> {
protected:
	void Config() {
		setSlug("toki-oc-nov-16-daging-dan-telur");
		setTimeLimit(1); // 0.1
		setMemoryLimit(16);
	}

	void SampleTestCases() {
		SAMPLE_CASE({"4", "0 1 0 0"}, {1});
	}

	void TestGroup1() {
		assignToSubtasks({1});
		
		for (int start = 0; start <= 1; start++) {
			CASE(N = 1; ManualArray(start,{1}));
			CASE(N = 2; ManualArray(start,{2}));
			CASE(N = 3; ManualArray(start,{3}));
			CASE(N = 99; ManualArray(start,{99}));
			CASE(N = 100; ManualArray(start,{100}));
			
			CASE(N = 2; ManualArray(start,{1,1}));
			CASE(N = 3; ManualArray(start,{1,1,1}));
			CASE(N = 10; ManualArray(start,{1,1,1,1,1,1,1,1,1,1}));
			CASE(N = 77; ManualArray(start,{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}));
			CASE(N = 100; ManualArray(start,{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}));
		
			CASE(N = 3; ManualArray(start,{1,2}));
			CASE(N = 3; ManualArray(start,{2,1}));
			CASE(N = 6; ManualArray(start,{1,5}));
			CASE(N = 6; ManualArray(start,{5,1}));
			CASE(N = 98; ManualArray(start,{1,97}));
			CASE(N = 98; ManualArray(start,{97,1}));
			CASE(N = 99; ManualArray(start,{1,98}));
			CASE(N = 99; ManualArray(start,{98,1}));
			CASE(N = 100; ManualArray(start,{1,99}));
			CASE(N = 100; ManualArray(start,{99,1}));
			
			CASE(N = 4; ManualArray(start,{1,2,1}));
			CASE(N = 4; ManualArray(start,{2,1,1}));
			CASE(N = 10; ManualArray(start,{4,6}));
			CASE(N = 10; ManualArray(start,{7,1,2}));
			CASE(N = 42; ManualArray(start,{40,2}));
			CASE(N = 42; ManualArray(start,{3,39}));
			CASE(N = 88; ManualArray(start,{44,44}));
			CASE(N = 88; ManualArray(start,{43,45}));
			CASE(N = 97; ManualArray(start,{49,48}));
			CASE(N = 97; ManualArray(start,{10,20,10,8,1,8,10,20,10}));
		}
		
		CASE(N = 4; RandomArray(1,3));
		CASE(N = 8; RandomArray(7,1));
		CASE(N = 13; RandomArray(2,11));
		CASE(N = 33; RandomArray(29,4));
		CASE(N = 49; RandomArray(24,25));
		CASE(N = 66; RandomArray(33,33));
		CASE(N = 76; RandomArray(39,37));
		CASE(N = 89; RandomArray(29,60));
		CASE(N = 99; RandomArray(75,24));
		CASE(N = 100; RandomArray(50,50));
		
		CASE(N = 4; PureRandom(4));
		CASE(N = 17; PureRandom(17));
		CASE(N = 23; PureRandom(23));
		CASE(N = 46; PureRandom(46));
		CASE(N = 50; PureRandom(50));
		CASE(N = 64; PureRandom(64));
		CASE(N = 77; PureRandom(77));
		CASE(N = 81; PureRandom(81));
		CASE(N = 94; PureRandom(94));
		CASE(N = 100; PureRandom(100));
	}
	
	void ManualArray(int init, vector<int> freq) {
		A.clear();
		for (int i = 0; i < freq.size(); i++) {
			for (int j = 0; j < freq[i]; j++) A.push_back(init);
			init ^= 1;
		}
	}
	
	void RandomArray(int egg, int meat) {
		A.clear();
		for (int i = 0; i < egg; i++) A.push_back(0);
		for (int i = 0; i < meat; i++) A.push_back(1);
		rnd.shuffle(A.begin(),A.end());
	}
	
	void PureRandom(int N) {
		A.clear();
		for (int i = 0; i < N; i++) A.push_back(rnd.nextInt(2));
	}
};

int main(int argc, char* argv[]) {
	Runner<Problem> runner(argc, argv);

	runner.setGenerator(new Generator());
	return runner.run();
}

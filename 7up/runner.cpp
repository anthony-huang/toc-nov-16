#include <bits/stdc++.h>
#include <tcframe/runner.hpp>
using namespace std;
using namespace tcframe;

const vector<string> POOL = {"AH", "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "10H", "JH", "QH", "KH", "AS", "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "10S", "JS", "QS", "KS", "AC", "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "10C", "JC", "QC", "KC", "AD", "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "10D", "JD", "QD", "KD"};

class Problem : public BaseProblem {
protected:
	int N;
	vector<string> inp;
	vector<vector<string>> ans;

	void Config() {
		setSlug("toki-oc-nov-16-7up");
		setTimeLimit(1);
		setMemoryLimit(64);
	}

	void InputFormat() {
		LINE(N);
		LINES(inp) % SIZE(N);
	}

	void OutputFormat() {
		GRID(ans) % SIZE(N, 12);
	}

	void Subtask1() {
		CONS(1 <= N && N <= 1000);
		CONS(inp.size() == N);
		CONS(IsValid(inp, POOL));
	}

	bool IsValid(const vector<string>& vec, const vector<string>& POOL) {
		for (const auto& item : vec) {
			if (find(POOL.begin(), POOL.end(), item) == POOL.end())
				return 0;
		}
		return 1;
	}
};

class Generator : public BaseGenerator<Problem> {
protected:
    void Config() {
        setTestCasesDir("tc");
        setSolutionCommand("./solution");
    }

    void SampleTestCases() {
        SAMPLE_CASE({
            "3", "7H", "8S", "5C"
        }, {1});
    }

	inline string ChooseOne(const vector<string>& POOL) {
		return POOL[rnd.nextInt(POOL.size())];
	}

	void TestGroup1() {
		assignToSubtasks({1});

		CASE(N = 1000, Generate(N, inp));
		CASE(N = 500, Generate(N, inp));
		CASE(N = 100, Generate(N, inp));
	}

	void Generate(int& N, vector<string>& vec) {
		vec.clear();
		for (int i = 0; i < N; ++i) vec.push_back(ChooseOne(POOL));
		return ;
	}
};

int main(int argc, char* argv[]) {
	Runner<Problem> runner(argc, argv);

	runner.setGenerator(new Generator());
	return runner.run();
}

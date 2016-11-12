#include <bits/stdc++.h>
#include <tcframe/runner.hpp>
using namespace std;
using namespace tcframe;

const int MAX_LEN = 1000000;
const string SIGMA = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

class Problem : public BaseProblem {
protected:
	string s;
	int K;
	vector<int> ans;

	void Config() {
		setSlug("toki-oc-nov-16-typeracing");
		setTimeLimit(2);
		setMemoryLimit(64);
	}

	void InputFormat() {
		LINE(s);
	}

	void OutputFormat() {
		LINE(K);
		LINE(ans % SIZE(K));
	}

	void Subtask1() {
		CONS(1 <= s.length() && s.length() <= MAX_LEN);
		CONS(IsAlnum(s));
	}

	bool IsAlnum(const string& s) {
		for (const auto& c : s) {
			if (!isalnum(c)) {
				return 0;
			}
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
            "sayamaksaysayamakannasi"
        }, {1});
        SAMPLE_CASE({
            "aaaaaa"
        }, {1});
    }

	void Random(const int length, string& s, const string& SIGMA) {
		s = "";
		for (int i = 0; i < length; ++i) {
			s.push_back(SIGMA[rnd.nextInt(SIGMA.length())]);
		}
		return ;
	}

	void RandomPrefix(const int length, const int longest_length, string& s, const string& SIGMA) {
		s = "";
		string utama = SIGMA;
		for (int i = 0; i < longest_length - SIGMA.length(); ++i) {
			utama.push_back(SIGMA[rnd.nextInt(SIGMA.length())]);
		}
		rnd.shuffle(utama.begin(), utama.end());

		vector<string> vec;
		vec.clear();
		vec.push_back(utama);
		int total_length = longest_length;
		while (total_length < length) {
			int max_len = (longest_length, length - total_length);
			const string& prefix = utama.substr(0, rnd.nextInt(max_len) + 1);
			vec.push_back(prefix);
			total_length += prefix.length();
		}

		rnd.shuffle(vec.begin(), vec.end());
		for (const auto& ss : vec) {
			s.append(ss);
		}

		return ;
	}

	void TestGroup1() {
		assignToSubtasks({1});

		CASE(s = "abcdabcababd");
		CASE(s = "0");
		CASE(s = "A");
		CASE(s = "aAaAaAaAaA");
		CASE(s = "aAaAaAaAa");
		
		CASE(Random(MAX_LEN, s, "a"));
		CASE(Random(MAX_LEN, s, "0"));
		CASE(Random(MAX_LEN, s, "A"));
		CASE(Random(MAX_LEN, s, "ab"));
		CASE(Random(MAX_LEN, s, "ab"));
		CASE(Random(MAX_LEN, s, "abc"));
		CASE(Random(MAX_LEN, s, "abc"));
		CASE(Random(MAX_LEN, s, "0Aa"));
		CASE(Random(MAX_LEN, s, "0Aa"));

		CASE(Random(MAX_LEN, s, SIGMA));
		CASE(Random(MAX_LEN, s, SIGMA));
		CASE(Random(MAX_LEN, s, SIGMA));
		CASE(Random(MAX_LEN, s, SIGMA));
		CASE(Random(MAX_LEN, s, SIGMA));
		CASE(Random(MAX_LEN, s, SIGMA));
		CASE(Random(MAX_LEN, s, SIGMA));
		CASE(Random(MAX_LEN, s, SIGMA));
		CASE(Random(MAX_LEN, s, SIGMA));
		CASE(Random(MAX_LEN, s, SIGMA));

		CASE(RandomPrefix(MAX_LEN, 100, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 100, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 100, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 100, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 500, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 500, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 500, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 500, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 1000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 1000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 1000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 1000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 5000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 5000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 5000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 5000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 10000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 10000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 10000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 10000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 50000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 50000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 50000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 50000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 100000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 100000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 100000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 100000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 500000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 500000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 500000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, 500000, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, MAX_LEN, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, MAX_LEN, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, MAX_LEN, s, SIGMA));
		CASE(RandomPrefix(MAX_LEN, MAX_LEN, s, SIGMA));
	}
};

int main(int argc, char* argv[]) {
	Runner<Problem> runner(argc, argv);

	runner.setGenerator(new Generator());
	return runner.run();
}

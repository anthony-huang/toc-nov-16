#include <bits/stdc++.h>
#include <tcframe/runner.hpp>
using namespace std;
using namespace tcframe;

const int MAXN = 100000;

class Problem : public BaseProblem {
protected:
    int N, Q;
    vector<int> arr;
    vector<int> result;
    vector<int> L, R;

    void Config() {
        setSlug("toki-oc-nov-16-2min");
        setTimeLimit(1);
        setMemoryLimit(32);
    }

    void InputFormat() {
        LINE(N);
        LINE(arr % SIZE(N));
        LINE(Q);
        LINES(L, R) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(result) % SIZE(Q);
    }

    void Subtask1() {
        CONS(1 <= N && N <= MAXN);
        CONS(isPermutation(arr, N));
        CONS(isValid(L, R, N, Q));
    }

    bool isPermutation(const vector<int>& v, const int& N) {
        if (v.size() != N) return false;
        bitset<MAXN + 1> bs;
        for (int i = 0; i < v.size(); ++i) {
            if (bs[v[i]])
                return false;
            bs[v[i]] = 1;
        }
        return true;
    }

    bool isValid(const vector<int>& l, const vector<int>& r, const int& n, const int& q) {
        if (l.size() != q || r.size() != q)
            return false;
        for (int i = 0; i < q; ++i) {
            if (!(1 <= l[i] && l[i] <= r[i] && r[i] <= n)) {
                return false;
            }
        }
        return true;
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
            "10",
            "7 1 3 6 4 9 10 5 2 8",
            "3",
            "3 5",
            "6 9",
            "2 7"
        }, {1});
    }

    void randomShuffle(vector<int>& v) {
        for (int i = 1; i < v.size(); ++i) {
            swap(v[rnd.nextInt(0, i)], v[i]);
        }
    }

    void gen(bool needShuffle = false, bool needReverse = false) {
        arr = vector<int>(N);
        for (int i = 0; i < N; ++i) {
            arr[i] = i + 1;
        }
        if (needShuffle)
            randomShuffle(arr);
        if (needReverse)
            reverse(arr.begin(), arr.end());
    }

    void genIntervals(int N, int Q) {
        L = R = vector<int>(Q);
        for (int i = 0; i < Q; ++i) {
            L[i] = rnd.nextInt(1, N);
            R[i] = rnd.nextInt(L[i], N);
        }
    }

    void TestGroup1() {
        assignToSubtasks({1});
        CASE(N = MAXN, Q = MAXN, gen(), genIntervals(N, Q));
        CASE(N = MAXN, Q = MAXN, gen(true), genIntervals(N, Q));
        CASE(N = MAXN, Q = MAXN, gen(true, true), genIntervals(N, Q));
        CASE(N = MAXN, Q = MAXN, gen(false, true), genIntervals(N, Q));
        CASE(N = MAXN, Q = MAXN, gen(true), L = vector<int>(Q, 1), R = vector<int>(Q, N));
        CASE(N = MAXN - 1, Q = MAXN, gen(), genIntervals(N, Q));
        CASE(N = MAXN, Q = MAXN, gen(true), genIntervals(N, Q));
        CASE(N = 1, Q = 10, gen(), L = vector<int>(Q, 1), R = vector<int>(Q, 1));
    }
};

int main(int argc, char* argv[]) {
    Runner<Problem> runner(argc, argv);

    runner.setGenerator(new Generator());
    return runner.run();
}

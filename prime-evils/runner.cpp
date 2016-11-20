#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class Problem : public BaseProblem {
 protected:
  int N;
  long long K;
  vector<int> A;
  vector<string> ANS;

  void InputFormat() {
    LINE(N, K);
    LINE(A % SIZE(N));
  }

  void OutputFormat() {
    LINE(ANS);
  }

  void Subtask1() {
    CONS(1 <= N && N <= (int)1e5);
    CONS(1 <= K && K <= (long long)1e11);
    CONS(eachElementBetween(A,1,1e6));
  }

private:
  bool eachElementBetween(vector<int> v,int lo,int hi) {
    for(int x : v)
      if(x < lo || x > hi)
        return 0;
    return 1;  
  }
};

class Generator : public BaseGenerator<Problem> {
protected:
  vector<int> primes;

  void Config() {
    setSlug("toki-oc-nov-2016-prime-evils");
    setTimeLimit(1);
    setMemoryLimit(64);    
  }

  void SampleTestCases() {
    SAMPLE_CASE({"5 42","4 8 10 18 30"},{1});
    SAMPLE_CASE({"5 42","8 4 19 11 31"},{1});
    SAMPLE_CASE({"6 2770","100 235 423 616 630 766"},{1});
  }

  void TestGroup1() {
    assignToSubtasks({1});
    
    primes = generatePrimes(1e6);

    // anti 1=prima
    CASE(N = 5,
         K = 3,
         A = {1,1,1,1,1});

    // big primes
    CASE(N = 100000,
         K = rnd.nextLongLong(1e7,1e11),
         A = allPrime(N,4e5,1e6));

    // all biggest prime
    CASE(N = 100000,
         K = rnd.nextLongLong(1,1e11),
         A = randomArray(N,primes.back(),primes.back()));

    for(int i = 0 ; i < 3 ; i++) {

      // pure random
      CASE(N = rnd.nextInt(80000,100000), 
           K = rnd.nextLongLong(1,1e11),
           A = randomArray(N,1,1e6));

      // K capped at sum
      CASE(N = rnd.nextInt(80000,100000),
           A = randomArray(N,1,1e6),
           K = rnd.nextLongLong(1,accumulate(A.begin(),A.end(),0LL)));

      // answer is 0/1
      CASE(N = rnd.nextInt(80000,100000),
           A = allPrime(N,1,1e6),
           K = rnd.nextLongLong(1,(long long)1e11));

      // no prime
      CASE(N = rnd.nextInt(80000,100000),
           A = noPrime(N,1,1e6),
           K = rnd.nextLongLong(1,accumulate(A.begin(),A.end(),0LL)));

      // random, K >= sum
      CASE(N = rnd.nextInt(80000,100000),
           A = randomArray(N,1,1e6),
           K = rnd.nextLongLong(accumulate(A.begin(),A.end(),0LL), (long long)1e11));

      // One Punch!
      CASE(N = rnd.nextInt(80000,100000),
           A = noPrime(N,1,1e6),
           K = rnd.nextLongLong(accumulate(A.begin(),A.end(),0LL), (long long)1e11));

      // single prime, not part of optimal solution
      CASE(N = rnd.nextInt(80000,100000),
           A = noPrime(N-1,1,5e5), add(A,allPrime(1,5e5,1e6)),
           K = accumulate(A.begin(), A.end(), 0LL) - rnd.nextInt(1,A.back()),
           rnd.shuffle(A.begin(),A.end()));

      // single prime, one punch!
      CASE(N = rnd.nextInt(80000,100000),
           A = noPrime(N-1,1,1e6), add(A,allPrime(1,1,1e6)),
           K = rnd.nextLongLong(accumulate(A.begin(), A.end(), 0LL), 1e11),
           rnd.shuffle(A.begin(), A.end()));
    }
  }

private:

  void add(vector<int> &a,vector<int> b) {
    for(int x : b)
      a.push_back(x);
  }

  vector<int> generatePrimes(int mx) {
    vector<int> ret;
    vector<bool> flag(mx+1,1);

    for(int i = 2 ; i <= mx ; i++)
      if(flag[i]) {
        ret.push_back(i);

        for(int j = i+i ; j <= mx ; j += i)
          flag[j] = 0;
      }

    return ret;  
  }

  vector<int> randomArray(int n,int lo,int hi) {
    vector<int> ret(n);
    for(int i = 0 ; i < n ; i++)
      ret[i] = rnd.nextInt(lo,hi);
    return ret;
  }

  vector<int> allPrime(int n,int lo,int hi) {
    vector<int> ret(n);
    lo = lower_bound(primes.begin(), primes.end(), lo) - primes.begin();
    hi = upper_bound(primes.begin(), primes.end(), hi) - primes.begin() - 1;

    for(int i = 0 ; i < n ; i++)
      ret[i] = primes[rnd.nextInt(lo,hi)];
    return ret;
  }

  vector<int> noPrime(int n,int lo,int hi) {
    vector<int> ret(n);
    for(int i = 0 ; i < n ; i++) {
      ret[i] = rnd.nextInt(lo,hi);
      while(binary_search(primes.begin(), primes.end(), ret[i]))
        ret[i] = rnd.nextInt(lo,hi);
    }
    return ret;
  }
};

int main(int argc, char* argv[]) {
  Runner<Problem> runner(argc, argv);

  runner.setGenerator(new Generator());
  return runner.run();
}

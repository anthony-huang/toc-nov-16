#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

const int MAXLOG = 2000;

class Problem : public BaseProblem {
 protected:
  string A, B;
  int K;
  int ANS;

  void InputFormat() {
    LINE(A);
    LINE(B);
    LINE(K);
  }

  void OutputFormat() {
    LINE(ANS);
  }

  void Subtask1() {
    CONS(1 <= A.length() && A.length() <= MAXLOG+1);
    CONS(1 <= B.length() && B.length() <= MAXLOG+1);
    CONS(lessOrEqual(A,B));

    CONS(noLeadingZero(A));
    CONS(noLeadingZero(B));
    CONS(isBinary(A));
    CONS(isBinary(B));

    CONS(1 <= K && K <= MAXLOG);
  }

private:
  bool lessOrEqual(string a, string b) {
    if(a.length() < b.length()) return 1;
    if(b.length() < a.length()) return 0;

    for(int i = 0 ; i < a.length() ; i++)
      if(a[i] > b[i])
        return 0;

    return 1;  
  }

  bool noLeadingZero(string s) {
    return s[0] != '0';
  }

  bool isBinary(string s) {
    for(int i = 0 ; i < s.length() ; i++)
      if(s[i] != '0' && s[i] != '1')
        return 0;
    return 1;  
  }
};

class Generator : public BaseGenerator<Problem> {
protected:
  void Config() {
    setSlug("toki-oc-nov-2016-bit");
    setTimeLimit(1);
    setMemoryLimit(64);    
  }

  void SampleTestCases() {
    SAMPLE_CASE({"101","10100","2"},{1});
    SAMPLE_CASE({"1010","10011","3"},{1});
    SAMPLE_CASE({"111000111","1110001111","4"},{1});
  }

  void TestGroup1() {
    assignToSubtasks({1});
    
    CASE(A = lowerBound(), B = upperBound(), K = MAXLOG);
    CASE(A = randomBinaryString(1,MAXLOG), B = randomBinaryString(1,MAXLOG), fix(), K = rnd.nextInt(1,MAXLOG));
    CASE(A = randomBinaryString(2,1000), B = randomBinaryString(2,1000), fix(), K = B.length()-1);
    CASE(A = randomBinaryString(1900,2000), B = randomBinaryString(1900,2000), fix(), K = 1);
    CASE(A = lowerBound(), B = upperBound(), K = MAXLOG-1);

    for(int i = 0 ; i < 5 ; i++)
      CASE(A = lowerBound(), B = upperBound(), K = rnd.nextInt(1,MAXLOG));

    for(int i = 0 ; i < 10 ; i++) {
      CASE(A = randomBinaryString(1,MAXLOG), B = randomBinaryString(1,MAXLOG), fix(), K = rnd.nextInt(1,B.length()));
      CASE(A = randomBinaryString(1500,MAXLOG), B = randomBinaryString(1500,MAXLOG), fix(), K = rnd.nextInt(1,B.length()));
    }

    for(int i = 0 ; i < 5 ; i++) {
      CASE(K = rnd.nextInt(1,MAXLOG-2), 
           A = binaryStringWithKStep(rnd.nextInt(K+2,MAXLOG),K), 
           B = binaryStringWithKStep(rnd.nextInt(K+2,MAXLOG),K),
           fix());

      CASE(K = rnd.nextInt(1,MAXLOG-2), 
           A = binaryStringWithKStep(rnd.nextInt(K+2,MAXLOG),K), 
           B = randomBinaryString(1500,MAXLOG),
           fix());

      CASE(K = rnd.nextInt(1,MAXLOG-2), 
           A = randomBinaryString(1,777), 
           B = binaryStringWithKStep(rnd.nextInt(K+2,MAXLOG),K),
           fix());

      CASE(K = rnd.nextInt(1,MAXLOG/2), 
           A = binaryStringWithKStep(rnd.nextInt(K+2,MAXLOG),K), 
           B = randomBinaryString(1950,MAXLOG),
           fix());
    }
  }

private:

  string upperBound() {
    string ret = "1";
    for(int i = 0 ; i < MAXLOG ; i++)
      ret += "0";
    return ret;
  }

  string lowerBound() {
    return "1";
  }

  string randomBinaryString(int low,int hi) {
    int len = rnd.nextInt(low,hi);
    string ret = "1";
    for(int i = 1 ; i < len ; i++)
      ret += (char)rnd.nextInt('0','1');
    return ret;
  }

  string binaryStringWithKStep(int len,int k) {
    string ret = "1";
    for(int i = 1 ; i < len ; i++)
      ret += "1";

    int lsb = rnd.nextInt(k,len-1);
    for(int i = lsb+1 ; i < len ; i++)
      ret[i] = '0';

    if(lsb > 1) {
      vector<int> pos(lsb-1);
      iota(pos.begin(),pos.end(),1);
      rnd.shuffle(pos.begin(),pos.end());

      for(int i = 0 ; i < k-1 ; i++) 
        ret[pos[i]] = '0';
    }

    return ret;
  }

  bool lessOrEqual(string a, string b) {
    if(a.length() < b.length()) return 1;
    if(b.length() < a.length()) return 0;

    for(int i = 0 ; i < a.length() ; i++)
      if(a[i] > b[i])
        return 0;

    return 1;  
  }

  void fix() {
    if(!lessOrEqual(A,B))
      swap(A,B);
  }
};

int main(int argc, char* argv[]) {
  Runner<Problem> runner(argc, argv);

  runner.setGenerator(new Generator());
  return runner.run();
}

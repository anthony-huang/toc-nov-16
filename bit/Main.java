import java.util.Scanner;

public class Main {

	private final static int N = 2005;
	private final static int MOD = 1000000007;

	private static int C[][];

	private static void precompute() {
		C = new int[N][N];

		for(int i = 0 ; i < N ; i++) {
			C[i][0] = 1;
			for(int j = 1 ; j <= i ; j++) {
				C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
			}
		}
	}

	private static int getComb(int a,int b) {
		if(a < 0 || b < 0 || a < b) {
			return 0;
		}
		return C[a][b];
	}

	private static String decrement(String s) {
		char ch[] = s.toCharArray();
		int cur = ch.length-1;

		while(ch[cur] == '0') {
			ch[cur] = '1';
			cur--;
		}
		ch[cur] = '0';

		String ret = "";
		for(int i = 0 ; i < ch.length ; i++)
			ret += ch[i];
		if(ret.charAt(0) == '0')
			ret = ret.substring(1);

		return ret;
	}

	private static int calc(String s,int k) {
		if(s.length() == 0) return 0;

		int ret = 0;
		for(int i = 1 ; i < s.length() ; i++)
			for(int j = i+1 ; j < s.length() ; j++) {
				ret = (ret + getComb(j-i-1,k-1)) % MOD;
			}

		int zero = 0;
		for(int i = 1 ; i < s.length() ; i++) {
			if(s.charAt(i) == '0') {
				zero++;
			}
			else {
				if(zero+1 == k) {
					ret = (ret + 1) % MOD;
				}

				zero++;

				for(int j = i+1 ; j < s.length() ; j++)
					ret = (ret + getComb(j-i-1,k-zero-1)) % MOD;

				zero--;
			}
		}

		return ret;	
	}

	public static void main(String[] args) {
		precompute();
		
		Scanner in = new Scanner(System.in);
		String a = in.nextLine();
		String b = in.nextLine();
		int k = in.nextInt();

		a = decrement(a);
		int ret = b.length() - a.length();
		if(k > 0) {
			ret = (calc(b,k) - calc(a,k) + MOD) % MOD;
		}
		System.out.println(ret);
	}
}
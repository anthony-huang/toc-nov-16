import java.io.*;
import java.util.*;

public class Main {
	public static final int MOD = 1000000009;
	public static final int BASE = 63;
	public static final int BAGI_BASE = 984126993;
	public static final int MAXLEN = 1000005;
	public static final String SIGMA = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	private static int take_hash(int l, int length, int[] hash, int[] bagi_base) {
		int r = l + length - 1;
		if (l == 0) return hash[r];
		int tmp = hash[r] - hash[l - 1];
		if (tmp < 0) tmp += MOD;
		tmp = (int)((1L * tmp * bagi_base[l]) % MOD);
		return tmp;
	}

	public static void main(String[] argv) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		String s = br.readLine();

		int[] mapping = new int[256];
		for (int i = 0; i < SIGMA.length(); ++i) {
			mapping[SIGMA.charAt(i)] = i + 1;
		}

		int[] bagi_base = new int[MAXLEN];
		bagi_base[0] = 1;
		for (int i = 1; i < MAXLEN; ++i) {
			bagi_base[i] = (int)((1L * bagi_base[i - 1] * BAGI_BASE) % MOD);
		}

		int[] hash = new int[MAXLEN];
		int pkt = 1;
		for (int i = 0; i < s.length(); ++i) {
			hash[i] = (int)((1L * pkt * mapping[s.charAt(i)]) % MOD);
			if (i > 0) {
				hash[i] += hash[i - 1];
				if (hash[i] >= MOD) hash[i] -= MOD;
			}
			pkt = (int)((1L * pkt * BASE) % MOD);
		}

		int[] stack = new int[MAXLEN];
		int longest = 0;
		int stack_size = 0;
		stack[stack_size++] = 0;
		for (int i = 1; i < s.length(); ++i) {
			stack[stack_size++] = i;
			int length = 1;
			while (stack_size - 1 != longest
					&& take_hash(stack[stack_size - 1], length, hash, bagi_base) !=
					take_hash(stack[longest], length, hash, bagi_base)) {
				--stack_size;
				length = Math.min(stack[longest + 1] - stack[longest], i - stack[stack_size - 1] + 1);
			}

			if (i - stack[stack_size - 1] + 1 > stack[longest + 1] - stack[longest]) {
				longest = stack_size - 1;
			}
		}

		bw.write("" + stack_size + "\n");
		for (int i = 0; i < stack_size; ++i) {
			if (i > 0) bw.write(" ");
			bw.write("" + (stack[i] + 1));
		}
		bw.write("\n");
		bw.flush();
	}
}

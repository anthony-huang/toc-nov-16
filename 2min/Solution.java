import java.io.*;
import java.util.*;

class Triplet implements Comparable<Triplet> {

	public int x, y, i;

	public Triplet(int x, int y, int i) {
		this.x = x;
		this.y = y;
		this.i = i;
	}

	public int compareTo(Triplet other) {
		if (y == other.y)
			return i - other.i;
		return y - other.y;
	}
}

class Solution {
	private static int ft[];
	private static int n;

	private static void update(int p, int v) {
		for (int i = p; i <= n; i += i & -i) {
			ft[i] += v;
		}
	}

	private static int query(int p) {
		int ans = 0;
		for (int i = p; i > 0; i -= i & -i) {
			ans += ft[i];
		}
		return ans;
	}

	private static int query(int l, int r) {
		return query(r) - query(l - 1);
	}

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		n = Integer.parseInt(br.readLine());
		int arr[] = new int[n];
		int idx[] = new int[n];
		int sz = 0;
		String input[] = br.readLine().split(" ");
		ft = new int[n + 1];
		ArrayList<Triplet> intervals = new ArrayList<Triplet>();
		for (int i = 0; i < n; ++i) {
			int x = Integer.parseInt(input[i]);
			while (sz > 0) {
				intervals.add(new Triplet(idx[sz - 1], i + 1, -1));
				if (arr[sz - 1] > x) {
					--sz;
				} else break;
			}
			arr[sz] = x;
			idx[sz++] = i + 1;
		}

		int q = Integer.parseInt(br.readLine());
		int ans[] = new int[q];
		for (int i = 0; i < q; ++i) {
			String tmp[] = br.readLine().split(" ");
			intervals.add(new Triplet(Integer.parseInt(tmp[0]), Integer.parseInt(tmp[1]), i));
		}

		Collections.sort(intervals);

		for (int i = 0; i < intervals.size(); ++i) {
			if (intervals.get(i).i < 0) {
				update(intervals.get(i).x, 1);
			} else {
				ans[intervals.get(i).i] = query(intervals.get(i).x, intervals.get(i).y);
			}
		}
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		for (int i = 0; i < q; ++i) {
			bw.write(ans[i] + "\n");
		}
		bw.flush();
		bw.close();
	}
}

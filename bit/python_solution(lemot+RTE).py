N = 2005;
MOD = 1000000007;



C = [[0 for j in range(N)] for i in range(N)]
for i in range(N):
	C[i][0] = 1
	for j in range(1,i+1):
		C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD

def getComb(a,b):
	if ((a < 0) or (b < 0) or (a < b)):
		return 0
	return C[a][b]

def decrement(s):
	cur = len(s)-1;

	while(s[cur] == '0'):
		s = s[:cur] + "1" + s[cur+1:]
		cur = cur-1

	if(cur == 0):
		s = s[1:]
	else:
		s = s[:cur] + "0" + s[cur+1:]

	return s

def calc(s,k):
	if len(s) == 0:
		return 0

	ret = 0
	for i in range(1,len(s)):
		for j in range(i+1,len(s)):
			ret = (ret + getComb(j-i-1,k-1)) % MOD

	zero = 0
	for i in range(1,len(s)):
		if s[i] == '0':
			zero = zero+1
		else:
			if zero+1 == k:
				ret = (ret + 1) % MOD

			zero = zero+1

			for j in range(i+1,len(s)):
				ret = (ret + getComb(j-i-1,k-zero-1)) % MOD

			zero = zero-1

	return ret

a = input()
b = input()
k = int(input())

a = decrement(a)
ret = len(b) - len(a)
if k > 0:
	ret = (calc(b,k) - calc(a,k) + MOD) % MOD
print(ret)			
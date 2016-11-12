MAXLEN 		= 1000005;
SIGMA 		= '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz';
BASE 		= 63;
MOD 		= 1000000009;
BAGI_BASE 	= 984126993;

bagi_base = [0 for _ in range(MAXLEN)]
bagi_base[0] = 1
for i in range(1, MAXLEN):
    bagi_base[i] = (bagi_base[i - 1] * BAGI_BASE) % MOD

mapping = {}
for i, c in enumerate(SIGMA):
    mapping[c] = i + 1

s = input()
_hash = [0 for _ in range(len(s))]
pkt = 1
for i, c in enumerate(s):
    _hash[i] = (pkt * mapping[c]) % MOD
    if i > 0:
        _hash[i] += _hash[i - 1]
        if _hash[i] >= MOD:
            _hash[i] -= MOD
    pkt = (pkt * BASE) % MOD

def take_hash(l, length):
    global _hash, r, tmp
    r = l + length - 1
    if l == 0:
        return _hash[r]
    tmp = _hash[r] - _hash[l - 1]
    if tmp < 0:
        tmp += MOD
    tmp = (tmp * bagi_base[l]) % MOD
    return tmp

stack = []
stack.append(0)
longest = 0
for i in range(1, len(s)):
    stack.append(i)
    length = 1
    while (len(stack) - 1 != longest) \
            and (take_hash(stack[-1], length) != take_hash(stack[longest], length)):
        stack.pop()
        if longest + 1 >= len(stack):
            length = min(i + 1 - stack[longest], i - stack[-1] + 1)
        else:
            length = min(stack[longest + 1] - stack[longest], i - stack[-1] + 1)
    if (longest + 1 < len(stack)) \
            and (i - stack[-1] + 1 > stack[longest + 1] - stack[longest]):
        longest = len(stack) - 1
    elif (longest + 1 >= len(stack)) \
            and (i - stack[-1] + 1 > i + 1 - stack[longest]):
        longest = len(stack) - 1

print(len(stack))
print(' '.join(str(x + 1) for x in stack))

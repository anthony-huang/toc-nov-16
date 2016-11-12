uses
	math;

const
	MAXLEN 		= 1000005;
	SIGMA 		= '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz';
	BASE 		= 63;
	_MOD 		= 1000000009;
	_BAGI_BASE 	= 984126993;

var
	s			: ansistring;
	hash		: array [0..MAXLEN] of longint;
	mapping 	: array ['0'..'z'] of longint;
	stack		: array [0..MAXLEN] of longint;
	stack_size	: longint;
	bagi_base	: array [0..MAXLEN] of longint;
	i, pkt		: longint;
	longest		: longint;
	length_used	: longint;

function take_hash (l : longint; _length : longint) : longint;
var
	r : longint;
begin
	r := l + _length - 1;
	take_hash := hash[r] - hash[l - 1];
	if take_hash < 0 then
		inc(take_hash, _MOD);
	take_hash := (int64(take_hash) * bagi_base[l - 1]) mod _MOD;
end;

begin
	for i := 0 to length(SIGMA) do
		mapping[SIGMA[i]] := i + 1;

	bagi_base[0] := 1;
	for i := 1 to MAXLEN do
		bagi_base[i] := (int64(bagi_base[i - 1]) * _BAGI_BASE) mod _MOD;

	readln(s);
	pkt := 1;
	for i := 1 to length(s) do begin
		hash[i] := (int64(pkt) * mapping[s[i]]) mod _MOD;
		inc(hash[i], hash[i - 1]);
		if hash[i] >= _MOD then
			dec(hash[i], _MOD);
		pkt := (int64(pkt) * BASE) mod _MOD;
	end;

	stack_size := 0;
	stack[stack_size] := 1;
	inc(stack_size, 1);
	longest := 0;
	for i := 2 to length(s) do begin
		stack[stack_size] := i;
		inc(stack_size, 1);
		length_used := 1;
		
		while (stack_size - 1 <> longest)
			and (take_hash(stack[stack_size - 1], length_used) <> take_hash(stack[longest], length_used))
			do begin
				dec(stack_size, 1);
				length_used := min(stack[longest + 1] - stack[longest], i - stack[stack_size - 1] + 1);
		end;
		
		if i - stack[stack_size - 1] + 1 > stack[longest + 1] - stack[longest] then
			longest := stack_size - 1;

	end;

	writeln(stack_size);
	for i := 0 to stack_size - 1 do begin
		if i > 0 then
			write(' ');
		write(stack[i]);
	end;
	writeln;
end.

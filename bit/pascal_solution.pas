const
	N = 2005;
	modd = 1000000007;

var
	C : array[0..N,0..N] of longint;
	A, B : ansistring;
	K : longint;

procedure precompute();
var
	i, j : longint;
begin
	for i := 0 to N do
		begin
			C[i][0] := 1;
			for j := 1 to i do
				C[i][j] := (C[i-1][j-1] + C[i-1][j]) mod modd; 
		end;
end;	

function getComb(d,e : longint) : longint;
begin
	if (d < 0) or (e < 0) or (d < e) then
		exit(0);
	exit(C[d][e]);
end;

function decrement(x : ansistring) : ansistring;
var
	cur : longint;
begin
	cur := length(x);
	while x[cur] = '0' do
	begin
		x[cur] := '1';
		dec(cur);
	end;
	x[cur] := '0';
	if cur = 1 then
		delete(x,1,1);
	exit(x);
end;	

function calc(s : ansistring) : longint;
var
	i, j: longint;
	ret, zero : longint;
	len : longint;
begin
	ret := 0;
	len := length(s);

	if len = 0 then
		exit(0);

	for i := 2 to len do
		for j := i+1 to len do
			ret := (ret + getComb(j-i-1,K-1)) mod modd;

	zero := 0;
	for i := 2 to len do
		if s[i] = '0' then
			inc(zero)
		else
			begin
				if zero+1 = K then
					ret := (ret + 1) mod modd;

				inc(zero);

				for j := i+1 to len do
					ret := (ret + getComb(j-i-1,k-zero-1)) mod modd;

				dec(zero);
			end;

	exit(ret);				
end;

begin
	precompute();

	readln(A);
	readln(B);
	readln(K);

	A := decrement(A);
	writeln((calc(B) - calc(A) + modd) mod modd);
end.	
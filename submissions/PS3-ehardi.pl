%PROBLEM 1

modadd(A,B,N,Result) :- Result is (A+B) mod N.
modmul(A,B,N,Result) :- Result is (A*B) mod N.

%PROBLEM 2
%perm(N, R, Result) :- 


%PROBLEM 3
fibo(A, _, 0, A).
fibo(_, B, 1, B).
fibo(A, B, N, Result) :- 
	N > 1, N1 is N - 1, N2 is N - 2, 
	fibo(A, B, N1, Result1), 
	fibo(A, B, N2, Result2), 
	Result is Result1 + Result2.


%PROBLEM 4
inverttri(N) :- N1 is N, N1 > 0, prints(N1), N1 is N-1, nl.
prints(N) :- between(1, N, _), write('*'), false.

startri(N) :- star(0, N).

star(C, X) :- C < X, count(0, C), C1 is C+1, star(C1, X).
star(C, X) :- C >= X.

count(X, Y) :- X =< Y, write('*'), X1 is X+1, count(X1,Y).
count(X, Y) :- X > Y, nl.

%PROBLEM 5
:-op(550,xf,genap).
X genap :- 0 is mod(X, 2).

:-op(550,xf,ganjil).
X ganjil :- 1 is mod(X, 2).

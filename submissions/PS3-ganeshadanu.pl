modadd(X, Y, Z, Result) :- Result is (X + Y) mod Z.
modmul(X, Y, Z, Result) :- Result is (X * Y) mod Z.

multi(MAX, MIN, Result) :-
    MAX > 0,
    MIN > 0,
    MAX =:= MIN,
    Result is 1.

multi(MAX, MIN, Result) :-
    MAX > MIN,
    MAX2 is MAX - 1,
    multi(MAX2, MIN, R2),
    Result is MAX * R2.

perm(N, R, Result) :-
    MIN is N - R,
    multi(N, MIN, Temp),
    Result is Temp mod ((10 ^ 9) + 7).

fibo(F1, _, 0, F) :- F is F1.
fibo(_, F2, 1, F) :- F is F2.
fibo(F1, F2, N, F) :-
    N > 1,
    N1 is N - 1,
    N2 is N - 2,
    fibo(F1, F2, N1, Fprev),
    fibo(F1, F2, N2, Fprev2),
    F is Fprev + Fprev2.

writeline(0) :- true.
writeline(Y) :- Y > 0,
    write('*'),
    Y2 is Y - 1,
    writeline(Y2).

inverttri(X) :-
    X >= 1,
    writeline(X),
    X2 is X - 1,
    nl,
    inverttri(X2).

drawtr(X, MAX) :-
    X < MAX,
    X2 is X + 1,
    writeline(X2),
    nl,
    drawtr(X2, MAX).
startri(X) :- drawtr(0, X).

:- op(700, xf, genap).
:- op(700, xf, ganjil).

X genap :- 0 =:= X mod 2.
X ganjil :- 1 =:= X mod 2.

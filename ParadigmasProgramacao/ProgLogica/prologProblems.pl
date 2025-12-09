/* interpretador: swipl
   run archive: [archive_name]
*/

/* membro - indentificar se um elemento esta em uma lista */
membro(E,[E|_]).
membro(E,[_|X]) :- membro(E,X).


/* inter - retornar a intersecção entre duas listas */

/* inter([1,2,3,4,5], [3,5,9,1], R).
R = [1,3,5] */

inter([],_,[]).
inter([A|As], L, [A|X]) :-
    membro(A,L),
    inter(As, L, X).
inter([_|As], L, X) :- inter(As,L,X).

/* ult - programa para indentificar o ultimo elemento */
ult([A], A).
ult([_|Xs], R) :- ult(Xs, R).

pen([A,_], A).
pen([_|Xs], R) :- pen(Xs, R).

/* msm - duas listas tem o mesmo tamanho */
msm([], []).
msm([_|As], [_|Bs]) :- msm(As, Bs).

/* duplica - duplica elementos de outra lista */
duplica([], []).
duplica([A|As], [A,A|X]) :- duplica(As, X).


/* delpri - deleta primeira ocorrencia de um elemento em uma lista */
delpri(_, [], []).
delpri(A, [A|As], As).
delpri(X, [A|As], [A|Lst]) :- delpri(X, As, Lst).

/* merge sort */
mergesort([], []).
mergesort([X],[X]).
mergesort(Lst, R) :-
               split(Lst, L1, L2),
               mergesort(L1, S1),
               mergesort(L2, S2),
               merge(S1,S2, R).

split([], [], []).
split([X], [X], []).
split([X,Y|Xs], [X|L1], [Y|L2]) :-
                split(Xs, L1, L2).

/* ordena chave-valor */
merge(L, [], L).
merge([], L, L).
merge([(F1,C1)|R1], [(F2, C2)|R2], [(F1,C1)|R]) :-
                    F1 =< F2,
                    merge(R1, [(F2, C2)|R2], R).
merge([(F1,C1)|R1], [(F2, C2)|R2], [(F2, C2)|R]) :-
                    merge([(F1,C1)|R1], R2, R).

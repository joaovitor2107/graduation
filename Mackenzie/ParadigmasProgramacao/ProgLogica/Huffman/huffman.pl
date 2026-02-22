% João Vitor de Araújo Trindade  - RA: 10403255
% Vinícius Pereira Rodrigues - RA: 10729470

:- use_module(library(readutil)).
:- use_module(library(lists)).

% ------------------------------------
% Entrada principal
% ------------------------------------
main :-
    read_file_to_string('in.txt', Content, []),
    string_chars(Content, Chars0),
    remove_last(Chars0, Chars),
    (Chars = [] -> writeln('Erro ao ler arquivo'), halt(1); true),
    count_elements(Chars, CountPairs),
    mergesort(CountPairs, SortedCounted),
    tuple_list_to_tree_list(SortedCounted, Trees),
    huffman(Trees, HuffmanTree),
    table_codes(HuffmanTree, Table),
    codify_text(Chars, Table, Binario),
    writeln(Table),
    open('out.txt', write, Stream),
    write(Stream, Binario),
    close(Stream),
    writeln('Arquivo out.txt gerado com sucesso!').

% ------------------------------------
% Remove último elemento (ex: \n)
% ------------------------------------
remove_last([], []).
remove_last([_], []).
remove_last([X|Xs], [X|Rest]) :- remove_last(Xs, Rest).

% ------------------------------------
% Conta ocorrências dos caracteres
% ------------------------------------
count_elements([], []).
count_elements(Chars, Pairs) :-
    unique_chars(Chars, Unique),
    count_each(Unique, Chars, Pairs).

% Gera lista sem duplicatas (ordem de primeira aparição)
unique_chars([], []).
unique_chars([X|Xs], [X|Rest]) :-
    not(member(X, Xs)), !,
    unique_chars(Xs, Rest).
unique_chars([X|Xs], Rest) :-
    member(X, Xs), !,
    unique_chars(Xs, Rest).

% Conta cada caractere da lista Unique dentro de Chars
count_each([], _, []).
count_each([C|Cs], Chars, [(N, C)|Rest]) :-
    count_in_list(C, Chars, N),
    count_each(Cs, Chars, Rest).

% Conta quantas vezes um elemento aparece
count_in_list(_, [], 0).
count_in_list(X, [X|Xs], N) :-
    count_in_list(X, Xs, N1),
    N is N1 + 1.
count_in_list(X, [_|Xs], N) :-
    count_in_list(X, Xs, N).

% ------------------------------------
% Ordenação
% ------------------------------------
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

merge(L, [], L).
merge([], L, L).
merge([(F1,C1)|R1], [(F2, C2)|R2], [(F1,C1)|R]) :-
                    F1 =< F2,
                    merge(R1, [(F2, C2)|R2], R).
merge([(F1,C1)|R1], [(F2, C2)|R2], [(F2, C2)|R]) :-
                    merge([(F1,C1)|R1], R2, R).

% ------------------------------------
% Converter tuplas (Freq, Char) em folhas da árvore
% ------------------------------------
tuple_list_to_tree_list([], []).
tuple_list_to_tree_list([(Freq, Char)|Xs], [f(Freq, Char)|Rest]) :-
    tuple_list_to_tree_list(Xs, Rest).

% ------------------------------------
% Inserção ordenada de nós (priority queue)
% ------------------------------------
add_ordered(A, [], [A]).
add_ordered(A, [X|Xs], [A,X|Xs]) :-
    get_freq(A, FA), get_freq(X, FX), FA =< FX, !.
add_ordered(A, [X|Xs], [X|Rest]) :-
    add_ordered(A, Xs, Rest).

% ------------------------------------
% Obter frequência de um nó
% ------------------------------------
get_freq(f(F, _), F).
get_freq(n(F, _, _), F).

% ------------------------------------
% Construir árvore de Huffman
% ------------------------------------
huffman([T], T) :- !.
huffman([T1, T2 | Rest], Tree) :-
    get_freq(T1, F1),
    get_freq(T2, F2),
    Fsum is F1 + F2,
    Node = n(Fsum, T1, T2),
    add_ordered(Node, Rest, NewList),
    huffman(NewList, Tree).

% ------------------------------------
% Criar tabela de códigos binários
% ------------------------------------
table_codes(f(_, Char), [(Char, "0")]) :- !.
table_codes(Tree, Table) :-
    table_codes_aux(Tree, "", Table).

table_codes_aux(f(_, Char), Bin, [(Char, Bin)]).
table_codes_aux(n(_, L, R), Bin, Table) :-
    string_concat(Bin, "0", BinL),
    string_concat(Bin, "1", BinR),
    table_codes_aux(L, BinL, TableL),
    table_codes_aux(R, BinR, TableR),
    append(TableL, TableR, Table).

% ------------------------------------
% Codificar texto para binário
% ------------------------------------
codify_text([], _, "").
codify_text([X|Xs], Table, Binario) :-
    codify_elem(X, Table, Code),
    codify_text(Xs, Table, Rest),
    string_concat(Code, Rest, Binario).

codify_elem(X, [(X, Code)|_], Code) :- !.
codify_elem(X, [_|Ys], Code) :-
    codify_elem(X, Ys, Code).

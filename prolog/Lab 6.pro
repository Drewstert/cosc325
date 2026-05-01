% male facts
male(brian).
male(matthew).
male(josiah).
male(tomjr).
male(tomsr).
male(richard).
male(richardjr).

% female facts
% female(X) means X is a female
female(analise).
female(beverly).
female(anne).
female(june).
female(kristine).
female(sharon).

% parent facts
% parent(X, Y) means X is the parent of Y
parent(brian,josiah).
parent(brian,analise).
parent(kristine,josiah).
parent(kristine,analise).
parent(tomjr,brian).
parent(tomjr,matthew).
parent(tomsr,tomjr).
parent(richard,beverly).
parent(richard,richardjr).
parent(richard,sharon).
parent(beverly,brian).
parent(beverly,matthew).
parent(anne,tomjr).
parent(june,beverly).
parent(june,richardjr).
parent(june,sharon).

father(X, Y) :- male(X), parent(X, Y).
mother(X, Y) :- female(X), parent(X, Y).
child(X, Y) :- parent(Y, X).
son(X, Y) :- child(X, Y), male(X).
daughter(X, Y) :- child(X, Y), female(X).
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).
grandfather(X, Y) :- grandparent(X, Y), male(X).
grandmother(X, Y) :- grandparent(X, Y), female(X).
sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.

% aunt/uncle facts
% uncle(X, Y) means X is the uncle of Y
% aunt(X, Y) means X is the aunt of Y
uncle(X, Y) :- male(X), parent(Z, Y), sibling(X, Z).
aunt(X, Y) :- female(X), parent(Z, Y), sibling(X, Z).

% reverse(R, L) means R is the reversed version of L
% Uses an accumulator for linear-time reversal of ismple (non-nested) lists
reverse(R, L) :- reverse_acc(L, [], R).
reverse_acc([], Acc, Acc).
reverse_acc([H|T], Acc, R) :- reverse_acc(T, [H|Acc], R).
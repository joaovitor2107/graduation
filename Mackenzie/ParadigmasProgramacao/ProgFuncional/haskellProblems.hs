tam [] = 0 -- uma lista vazia vale 0
tam(a:xs) = 1 + tam xs -- uma lista vale 1 + o tamanho da sua calda

member _ [] = False -- se tivermos lista vazia retorne False
member e (a:xs) -- temos que dado um valor que buscamos, e temos que nosso member é separado em head e tail
  | e == a = True -- se o elemento que buscamos for igual a retornamos True
  | otherwise = member e xs -- caso contrario passamos como lista para member e xs

------------------------

m [] [] = True
m (x:xs) [] = False
m [] (y:ys) = False
m (x:xs) (y:ys)
  | x /= y = False
  | otherwise = m xs ys

-----------------------

dup [] = []
dup (x:xs) = x:x:dup xs

-----------------------

delpri _ [] = []
delpri e (x:xs)
  | e == x = xs
  | otherwise = x:delpri e xs
-- quando estamos pensando em recursao devemos lembrar que é a cada call stack
-- que o x vai ser adicionado novamente, entao em cada delpri da recursao
-- lidamos so com o tail

-----------------------

del _ [] = []
del e (x:xs)
  | e == x = del e xs
  | otherwise = x:del e xs

----------------------

menor [] = 0
menor (x:xs) = men x xs

men m [] = m
men m (x:xs)
  | x < m = men x xs
  | otherwise = men m xs

----------------------
-- retorna elementos maiores que e
biggers _ [] = []
biggers e (x:xs)
  | x < e = biggers e xs
  | otherwise = x:biggers e xs

-- retorna elementos menores que e
menors _ [] = []
menors e (x:xs)
  | x >= e = menors e xs
  | otherwise = x:menors e xs



----------------------
mergesort [] = []
mergesort [x] = [x]
mergesort lst = merge (mergesort left) (mergesort right)
  where (left, right) = sp lst [] []

sp [] l1 l2 = (l1,l2)
sp [a] l1 l2 = (a:l1,l2)
sp (a:b:xs) l1 l2 = sp xs (a:l1) (b:l2)

merge xs [] = xs
merge [] ys = ys
merge (x:xs) (y:ys)
  | x <= y = x:merge xs (y:ys)
  | otherwise = y:merge (x:xs) ys

---------------------

-- segundo elemento + penultimo elemento
segundo (a:(b:xs)) = b

penultimo [a,_] = a
penultimo (x:xs) = penultimo xs

soma_s_p lst = (segundo lst) + (penultimo lst)

---------------------
-- quicksort
quicksort [] = []
quicksort [a] = [a]
quicksort (x:xs) = merge (quicksort l1) (x:quicksort l2)
-- aqui passamos o x:quicksort l2, por conta que se adicionarmos o pivo
-- novamente ficaremos com recursao infinita
  where (l1, l2) = split1 xs x

split1 lst x = sp1 lst x [] []
sp1 [] x l1 l2 = (l1,l2)
sp1 (y:ys) x l1 l2
  | y < x = sp1 ys x (y:l1) l2
  | otherwise = sp1 ys x l1 (y:l2)

---------------------
-- rld
rld [] = []
rld ((c,n):xs) = repet c n ++ rld xs

repet _ 0 = []
repet c n = c:repet c (n-1)

---------------------
-- basic
rle [] = []
rle (c:xs) = rlaux xs c 1

rlaux [] c n = [(c,n)]
rlaux (x:xs) c n
  | x == c = rlaux xs c (n+1)
  | otherwise = (c,n) : rlaux xs x 1

---------------------
-- Teoria dos sucessores
--data Nat = Z | S Nat
  --deriving (Show, Eq)

zero = Z
um = S Z
dois = S (S Z)
tres = S (S (S Z))

soma Z n = n
soma (S m) n = S(soma m n)

mult _ Z = Z
mult m (S n) = soma m (mult m n)

expo _ Z = S Z
expo Z _ = Z
expo m (S n) = mult m (expo m n )

conta Z = 0
conta (S n) = 1 + conta n

-- fazer subtracao, divisao, logaritimo

---------------------

-- para criar uma arvore
data Tree = F Integer | N Integer Tree Tree
  deriving (Eq, Show)

t1 = N 6 (N 3 (N 8 (F 5) (F 2)) (F 2))
  (N 2 (F 1) (F 2))


somaT (F n) = n
somaT (N n te td) = n + somaT te - somaT td

somaD (F n) = n
somaD (N n te td) = n + somaD td


height (F _) = 1
height (N _ te td) = 1 + maior (height te) (height td)

maior a b
  | a > b = a
  | otherwise = b


---------------------
int_to_pea 0 = Z
int_to_pea n = S(int_to_pea (n-1))

--------
data Naturals = Z | S Naturals
  deriving (Eq,Show)


zero1 = Z
um1 = S Z
soma1 Z n = n -- temos que Z(0) mais qualquer n é n
soma1 (S m) n = S(soma1 m n) --temos que uma soma é o sucessor de um numero + n é igual ao sucessor da soma de um numero + n

mult1 Z n = Z
mult1 _ Z = Z
mult1 (S m) n = soma1 (mult m n) n


sub n Z = n
sub Z m = m
sub (S n) (S m) = sub n m


div1 Z n = Z
div1 m n = divAux m n (S Z)
divAux m n divisor
  | mult divisor n == m = divisor
  | otherwise = divAux m n (S divisor)
-- temos que a divisao tem de ser 4/2 = 2
-- 6/2 = 3
-- duas possibilidades, tirar ate chegar no zero, ou adicionar ate chegar no numero

pot _ Z = S Z             --  m^n
pot m (S n) = mult m (pot m n)


log1 _ Z = S Z
log1 (S Z) _ = Z
log1 a b = logAux a b Z
logAux a b expo
  | pot b expo == a = expo
  | otherwise = logAux a b (S expo)

addOrdered e [] = [e]
addOrdered e (x:xs)
  | x > e = e:x:xs
  | otherwise = x:addOrdered e xs

orderList [] = []
orderList (x:xs) = addOrdered x (orderList xs)

-------------------

q2 [] = []
q2 (x:xs) = q2Aux x x ++ q2 xs
q2Aux a 0 = []
q2Aux a b = a:(q2Aux a (b-1))

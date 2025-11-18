-- Exercicio 1
-- Escreva o onde, que recebe um elemento e uma lista e devolve a posição da primeira ocorrência deste elemento na lista.
onde _ [] = 0
onde num lst = pos num lst 0

pos num [] position = position
pos num (x:xs) position
  | num == x = pos num [] (position+1)
  | otherwise = pos num xs (position+1)


-- Exercicio 2
-- Escreva o apos, que recebe um elemento elt e uma lista l e devolve a lista dos elementos de l que estão após o elemento elt.
apos num [] = []
apos num (x:xs)
  | x == num = xs
  | otherwise = apos num xs


-- Exercicio 3
-- Escreva o gera_n, que recebe um inteiro n e gera uma lista com a sequência dos naturais de 1 até n.

gera_n 0 = []
gera_n num = gera_lst num []

gera_lst 0 lst = lst
gera_lst num lst = gera_lst (num-1) (num:lst)


-- Exercicio 4
-- Sem usar como programa auxiliar o "tamanho da lista", escreva em Haskell o programa mtam, que recebe duas listas e responde se elas tem o mesmo tamanho.
mtam [] [] = True
mtam (x:xs) [] = False
mtam [] (y:ys) = False
mtam (x:xs) (y:ys) = mtam xs ys

-- Escreva a expressão lambda para a tabela verdade abaixo, sob o ponto de vista do X, conforme visto em aula.

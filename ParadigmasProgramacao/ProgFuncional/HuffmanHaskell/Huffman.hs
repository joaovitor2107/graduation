-- João Vitor de Araújo Trindade - RA: 10403255
-- Vinícius Pereira Rodrigues - RA: 10729470

import System.IO
import Control.Monad

main::IO()
main = do
  content <- readFile "in.txt" -- reads the entrance archive
  let text = removeLast content
  when (len text == 0) $
    error "Erro ao ler arquivo"
  print text
  let sorted_string = quicksort text -- para remover o \n da lista
  let countedElements = countElements sorted_string
  print countedElements
  let sortedCountedElements = quicksort countedElements
  print sortedCountedElements
  let treeList = tupleListToTreeList sortedCountedElements
  print treeList
  let arvore = huffman treeList
  let binario = codifyText text (tableCodes arvore)
  print (tableCodes arvore)
  when (len content > 0) $
    writeFile "out.txt" binario


len lst = lenAux lst 0

lenAux [] a = a
lenAux (x:xs) a = lenAux xs (a+1)

-- para ordenar a string para assim contarmos os quantidade de cada elemento
quicksort [] = []
quicksort [a] = [a]
quicksort (x:xs) = merge (quicksort s1) (x:quicksort s2)
  where (s1, s2) = split xs x

split lst x = sp lst x [] []
sp [] x l1 l2 = (l1,l2)
sp (y:ys) x l1 l2
  | y < x = sp ys x (y:l1) l2
  | otherwise = sp ys x l1 (y:l2)

merge xs [] = xs
merge [] ys = ys
merge (x:xs) (y:ys)
  | x < y = x:merge xs (y:ys)
  | otherwise = y:merge (x:xs) ys

-- para retirar a head e o elemento final de uma lista(por conta do \n)
removeHead [] = []
removeHead (x:xs) = xs

removeLast [] = []
removeLast [a] = []
removeLast (x:xs) = x:removeLast xs

-- para contar as ocorrencias de cada elemento na string
countElements [] = []
countElements (x:xs) = countElement xs x 1

countElement [] a n = [(n,a)]
countElement (x:xs) a n
  | x == a = countElement xs a (n+1)
  | otherwise = (n,a):countElement xs x 1

-- criando tipo arvore
data Tree = F Integer Char | N Integer Tree Tree
  deriving (Eq, Show)

--converter dados para tipo arvore
tupleToTree (freq,char) = F freq char

tupleListToTreeList [] = []
tupleListToTreeList (x:xs) = (tupleToTree x):tupleListToTreeList xs

-- para poder adcionar ordenamente o dado na arvore (basicamente uma priority queue)
addOrdered a [] = [a]
addOrdered a (x:xs)
  | getTimesAppeared x > getTimesAppeared a = a:x:xs
  | otherwise = x:addOrdered a xs

-- para pegar o dado de quantos vezes uma letra qualquer apareceu
getTimesAppeared (F a _) = a
getTimesAppeared (N a _ _) = a

-- construindo arvore de hufman !!!

huffman [a] = a
huffman (m1:m2:xs) =
  huffman (addOrdered (N (getTimesAppeared m1 + getTimesAppeared m2) m1 m2) xs)

-- fazendo a table de codigos binarios
tableCodes (F _ char) = [(char, "0")]
tableCodes tree = tableCodesAux tree ""

tableCodesAux (F _ char) bin = [(char, bin)]
tableCodesAux (N _ l r) bin =
  tableCodesAux l (bin++"0")  ++ tableCodesAux r (bin++"1")

--- codificando texto para bin
codifyElem x [] = error"Element wasnt on the list"
codifyElem x (y:ys)
  | x == getFirst y = getSecond y
  | otherwise = codifyElem x ys

codifyText [] table = ""
codifyText (x:xs) table = (codifyElem x table)++codifyText xs table

getFirst (a,b) = a
getSecond (a,b) = b

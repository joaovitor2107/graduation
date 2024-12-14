def bubble(nome, n):
    for i in range(n):
        for j in range(n - i - 1):
            if(nome[j][0] > nome[j + 1][0]):
                aux = nome[j]
                nome[j] = nome[j + 1]
                nome[j + 1] = aux

n = int(input())
k = int(input())

nome = [None] * n
for i in range(n):
    nome[i] = input()

bubble(nome, n)

for i in nome:
    print(i)

print(f"O vencedor foi {nome[k - 1]}")

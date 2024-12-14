def bubble(nome, n):
    for i in range(n):
        for j in range(n - i - 1):
            if(nome[j][0] > nome[j + 1][0]):
                aux = nome[j]
                nome[j] = nome[j + 1]
                nome[j + 1] = aux

n = int(input())

nomes = [None] * n
sla = 0
for i in range(n):
    sinal = input()   
    if(sinal == '+'):
        sla += 1
    nomes[i] = input()
bubble(nomes, sla)

for i in nomes:
    print(i)

print(f"Se compartaram: {sla} | Não se compartaram: {n - sla}")

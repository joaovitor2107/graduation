def calcular_painel_final(n, casos):
    resultados = []
    for caso in casos:
        painel_inicial, c = caso.split()
        c = int(c)
        painel = list(painel_inicial)
        estado_primeira = 'X' if c % 2 == 1 else painel[0]
        painel[0] = estado_primeira

        for i in range(1, len(painel)):
            if painel[i - 1] == 'X':  # A lâmpada à esquerda apagou
                painel[i] = 'O' if painel[i] == 'X' else 'X'

        resultados.append(''.join(painel))
    return resultados

n = int(input())
casos = [input().strip() for _ in range(n)]
resultados = calcular_painel_final(n, casos)

for resultado in resultados:
    print(resultado)


def bubble_sort(jogadores):
    n = len(jogadores)
    for i in range(n):
        trocou = False
        for j in range(0, n-i-1):
            if (jogadores[j][1] < jogadores[j+1][1]) or (jogadores[j][1] == jogadores[j+1][1] and jogadores[j][0] > jogadores[j+1][0]):
                jogadores[j], jogadores[j+1] = jogadores[j+1], jogadores[j]
                trocou = True
        if not trocou:
            break
    return jogadores

def main():
    n = int(input("Digite o número de jogadores: "))
    jogadores = []

    for _ in range(n):
        id, pontuacao = map(int, input("Digite o ID e a pontuação do jogador (separados por espaço): ").split())
        jogadores.append((id, pontuacao))

    jogadores_ordenados = bubble_sort(jogadores)

    print("Jogadores ordenados:")
    for jogador in jogadores_ordenados:
        print(f"ID: {jogador[0]}, Pontuação: {jogador[1]}")

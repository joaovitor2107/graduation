def organizar_atendimentos_bubble(emergencias):
    n = len(emergencias)
    
    for i in range(n):
        for j in range(0, n - i - 1):
            # Comparar os elementos adjacentes
            atual = emergencias[j]
            prox = emergencias[j + 1]
            
            if atual[0] < prox[0]:
                emergencias[j], emergencias[j + 1] = emergencias[j + 1], emergencias[j]
            
            elif atual[0] == prox[0] and atual[1] > prox[1]:
                emergencias[j], emergencias[j + 1] = emergencias[j + 1], emergencias[j]
    
    return emergencias

emergencias = [
    (5, "09:30"),
    (3, "10:00"),
    (5, "09:15"),
    (2, "10:30"),
    (4, "09:45")
]

resultado = organizar_atendimentos_bubble(emergencias)
print("Ordem de atendimento:")
for urgencia, horario in resultado:
    print(f"Urgência: {urgencia}, Horário: {horario}")


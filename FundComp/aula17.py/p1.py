def create_card():
    cartas = []
    valor = 128
    for _ in range(8):
        cartas.append(valor)
        valor //= 2
    return cartas


def bin_to_dec(valor_bin, cartas):
    decimal = 0
    for i in range(len(valor_bin)):
        if valor_bin[i] == '1':
            decimal += cartas[i]
    return decimal


def dec_to_bin(valor_dec, cartas):
    valor = int(valor_dec)
    binario = ""
    for carta in cartas:
        if carta <= valor:
            valor -= carta
            binario += "1"
        else:
            binario += "0"
    return binario


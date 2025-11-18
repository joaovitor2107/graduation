import math

def bisseccao(f, a: float, b: float, epsilon: float):
    p = (a + b)/2
    i = 0
    while abs(f(p)) > epsilon:

        if f(p) * f(a) < 0:
            b = p
        else:
            a = p

        p = (a + b)/2
        if i%10==0:
            print(f"Iteração {i}")
            print(f"f({p}): {f(p):.7f}")
        i += 1
        if i > 1000000:
            print("Valor não achado no intervalo")
            break

    return p


def fA(x):
    return x - 2**(-x)

def fB(x):
    e = math.e
    return e**x - x**2 + 3*x - 2

def fC(x):
    return 2*x*math.cos(2*x) - (x+1)**2

def fD(x):
    return x*math.cos(x) - 2*x**2 + 3*x - 1

def main():

    epsilon = 0.00001
    res_a = bisseccao(fA, 0, 1, epsilon)
    print("-------------------------------------")
    print(f"A raiz aproximada de A é p = {res_a}")
    print("-------------------------------------")

    res_b = bisseccao(fB, 0, 1, epsilon)
    print("-------------------------------------")
    print(f"A raiz aproximada de B é p = {res_b}")
    print("-------------------------------------")

    res_c = bisseccao(fC, -3, -2, epsilon)
    print("-------------------------------------")
    print(f"a raiz aproximada de c é p = {res_c}")
    res_c = bisseccao(fC, -1, 0, epsilon)
    print(f"a raiz aproximada de c é p = {res_c}")
    print("-------------------------------------")

    res_d = bisseccao(fD, 0.2, 0.3, epsilon)
    print("-------------------------------------")
    print(f"A raiz aproximada de D é p = {res_d}")

    res_d = bisseccao(fD, 1.2, 1.3, epsilon)
    print(f"A raiz aproximada de D é p = {res_d}")
    print("-------------------------------------")


if __name__ == "__main__":
    main()

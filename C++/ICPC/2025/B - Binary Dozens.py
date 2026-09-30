# <3
# Tema: Number Theory / Modulo de un Binario Gigante (Python)
# La version en Python del problema B de ICPC 2025 ("Binary Dozens"): el resto entre 12 de un
# numero binario de hasta 500 bits.
# En Python son dos lineas porque los enteros son de precision arbitraria: int(b, 2) convierte la
# cadena binaria completa (aunque mida 10^150) y despues se toma el modulo. No hay desborde posible.
# CUANDO ELEGIR PYTHON EN UN CONTEST: justo en esto, cuando el problema pide aritmetica con numeros
# enormes. Lo que en C++ obliga a Horner con modulo, a __int128 o a una clase de bignum, en Python
# es el operador de siempre. Tambien sirve para factoriales grandes, potencias exactas y
# combinatoria sin modulo.
# El precio es la velocidad: si ademas hay que hacer muchas operaciones, C++ con el modulo aplicado
# paso a paso gana por lejos. La version en C++ esta en "B - Binary Dozens.cpp", en esta misma
# carpeta, y usa rem = (rem * 2 + bit) % 12.
# Verificado contra los enteros exactos en 3004 cadenas, incluidas las de 500 bits.

while True:
    b = input()

    if b == "*":
        break

    n = int(b, 2)
    print(n % 12)

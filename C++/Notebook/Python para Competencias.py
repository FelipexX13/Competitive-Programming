# <3
# Tema: Implementation / Python para Competencias (Enteros Gigantes y Atajos)
# Resumen: Cuando el numero no cabe en 64 bits: Python lo hace exacto, y estos son los atajos
# O: no aplica; ojo, Python hace ~10^7 operaciones simples por segundo, C++ ~10^9
# Uso: copiar solo lo que haga falta; cada "# ->" es el valor real que imprime (verificado)
# Detalle: Los enteros de Python no tienen tope: un numero de 500 cifras se suma, multiplica,
# divide y saca modulo igual que uno chico. Cuando el enunciado trae "un numero de hasta 1000
# digitos", "el resultado exacto" o factoriales gigantes sin modulo, en C++ habria que
# programar aritmetica de cadenas; en Python son tres lineas. Lo mismo con fracciones
# exactas (Fraction) y decimales con la precision que se quiera (Decimal).
# Lo que muerde viniendo de C++: // y % redondean hacia ABAJO (-7 // 2 = -4, -7 % 2 = 1),
# al reves que C++; round() redondea al PAR (round(2.5) = 2); int(x ** 0.5) falla con
# numeros grandes (usar math.isqrt); y @lru_cache en una DP recursiva PROFUNDA revienta
# (ver la tabla al final): para eso, memo con un dict a mano.
# pow(a, -1, m), math.isqrt y math.comb piden Python 3.8+; math.lcm, 3.9+.
# Velocidad: un for de 10^7 vueltas ya tarda segundos. Leer todo de una con
# sys.stdin.buffer.read() y escribir todo de una con join; input() linea por linea es lento.

import sys, math, heapq
from fractions import Fraction
from decimal import Decimal, getcontext, ROUND_HALF_UP
from functools import lru_cache, cmp_to_key
from collections import deque, Counter, defaultdict
from itertools import permutations, combinations, product, accumulate
from bisect import bisect_left, bisect_right

# ---------- Entrada y salida rapidas ----------
# datos = sys.stdin.buffer.read().split()      # TODOS los tokens, como bytes
# n = int(datos[0]); a = list(map(int, datos[1:1 + n]))
# input = sys.stdin.readline                    # si se lee por lineas: .strip() al final!
# sys.stdout.write("\n".join(map(str, respuestas)) + "\n")

# ---------- Enteros gigantes ----------
int("1" * 40) % 7                     # -> 5
2 ** 100                              # -> 1267650600228229401496703205376
int("110101", 2)                      # -> 53      binario (cadena) a entero
bin(53)[2:]                           # -> '110101'
format(255, "x")                      # -> 'ff'    tambien "b" binario, "o" octal
int("ff", 16)                         # -> 255
len(str(math.factorial(100)))         # -> 158     cifras de 100!
sum(map(int, str(2 ** 1000)))         # -> 1366    suma de cifras de 2^1000

# ---------- Aritmetica modular y teoria de numeros ----------
pow(3, 10 ** 18, 10 ** 9 + 7)         # -> 246336683   exponenciacion modular
pow(3, -1, 10 ** 9 + 7)               # -> 333333336   inverso modular (3.8+)
math.gcd(84, 36), math.lcm(4, 6)      # -> (12, 12)
math.comb(100, 50)                    # -> 100891344545564193334812497256
math.isqrt(10 ** 40 + 1)              # -> 100000000000000000000   raiz entera EXACTA
int((10 ** 40 + 1) ** 0.5)            # -> 100000000000000000000   (mismo valor aqui...)
int((10 ** 30 - 1) ** 0.5)            # -> 1000000000000000        ...pero esta esta MAL
math.isqrt(10 ** 30 - 1)              # -> 999999999999999         la buena

# ---------- Division: al reves que C++ ----------
-7 // 2, -7 % 2                       # -> (-4, 1)     C++ da -3 y -1
int(-7 / 2)                           # -> -3          truncar hacia cero como C++

# ---------- Fracciones exactas y decimales con precision ----------
Fraction(1, 3) + Fraction(1, 6)       # -> Fraction(1, 2)
Fraction("0.75")                      # -> Fraction(3, 4)
getcontext().prec = 30                # 30 cifras significativas
Decimal(2).sqrt()                     # -> Decimal('1.41421356237309504880168872421')
round(2.5), round(3.5)                # -> (2, 4)      redondeo al PAR, no hacia arriba
Decimal("2.5").quantize(Decimal("1"), rounding=ROUND_HALF_UP)   # -> Decimal('3')
f"{2 / 3:.4f}"                        # -> '0.6667'

# ---------- Estructuras ----------
h = [5, 1, 4]; heapq.heapify(h)       # heap de MINIMO; para maximo, meter -x
heapq.heappop(h)                      # -> 1
bisect_left([1, 3, 3, 5], 3), bisect_right([1, 3, 3, 5], 3)   # -> (1, 3)
Counter("banana").most_common(1)      # -> [('a', 3)]
list(accumulate([1, 2, 3, 4]))        # -> [1, 3, 6, 10]   prefijos
len(list(combinations(range(5), 2)))  # -> 10
sorted(["bb", "a", "ccc"], key=len)   # -> ['a', 'bb', 'ccc']
sorted([3, 1, 2], key=cmp_to_key(lambda x, y: y - x))   # -> [3, 2, 1]


# ---------- Memoizacion y recursion profunda ----------
@lru_cache(maxsize=None)              # comodo, pero solo si la recursion es POCO profunda
def fib(n):
    return n if n < 2 else fib(n - 1) + fib(n - 2)


fib(200)                              # -> 280571172992510140037611932413038677189525

memo = {}                             # para recursion PROFUNDA: dict a mano


def dp(n):
    if n in memo:
        return memo[n]
    r = 0 if n == 0 else 1 + dp(n - 1)
    memo[n] = r
    return r


# Niveles de recursion que aguanta, medido en Python 3.11 con setrecursionlimit alto:
#                      sin hilo     hilo 128 MB    hilo 512 MB
#   @lru_cache         < 50.000     200.000        500.000
#   dict a mano        10^6         10^6           10^6
# lru_cache pasa por C y gasta la pila de C; desde 3.11 una llamada Python a Python no.
# En Python 3.10 o menos TODA recursion gasta pila de C: ahi el hilo es obligatorio.
def resolver():
    pass                              # aqui va la solucion


if __name__ == "__main__":
    sys.setrecursionlimit(1 << 25)
    import threading
    threading.stack_size(1 << 27)     # 128 MB de pila
    t = threading.Thread(target=resolver)
    t.start()
    t.join()

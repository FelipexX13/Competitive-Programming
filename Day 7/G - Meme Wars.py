# <3
# Tema: Math / Bit Manipulation
# Resuelve "Meme Wars": la palabra S(x) se define recursivamente como S(x) = S(p(x)) + x + S(p(x))
# (con S('a')='a', y p(x) la letra anterior), y hay que hallar la letra en la posicion n de la
# enorme palabra S('z').
# Esta es la clasica "ruler sequence": la letra en la posicion n depende unicamente de la mayor
# potencia de 2 que divide exactamente a n (su valuacion 2-adica). El diccionario dic mapea cada
# potencia de 2 a su letra correspondiente, y el bucle recorre las potencias en orden creciente
# guardando en 'cual' la ultima potencia que divide a n, hasta encontrar la primera que no lo
# divide; en ese momento imprime la letra asociada a esa ultima potencia (equivalente a contar
# los ceros finales de n en binario).

dic = {
    1: "a",
    2: "b",
    4: "c",
    8: "d",
    16: "e",
    32: "f",
    64: "g",
    128: "h",
    256: "i",
    512: "j",
    1024: "k",
    2048: "l",
    4096: "m",
    8192: "n",
    16384: "o",
    32768: "p",
    65536: "q",
    131072: "r",
    262144: "s",
    524288: "t",
    1048576: "u",
    2097152: "v",
    4194304: "w",
    8388608: "x",
    16777216: "y",
    33554432: "z"
}
n = int(input())
cual = 1
for clave,valor in dic.items():
    if(n%clave == 0):
        cual = clave
        continue
    else:
        print(dic[cual])
        break

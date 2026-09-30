# <3
# Tema: Math / Matrix Exponentiation
# Resuelve "Buses" (Maratona de Programacao da SBC 2013, problem H): dada una fila de longitud
# N metros formada por buses (10 m) y minibuses (5 m), con K colores posibles para minibus y L
# colores para bus, cuenta de cuantas formas distintas se puede armar la fila, entregando los
# ultimos 6 digitos del resultado.
# El numero de formas para una fila de largo 5*m sigue la recurrencia f(m) = k*f(m-1) + l*f(m-2)
# (agregar al final un minibus de cualquier color o un bus de cualquier color), como un
# Fibonacci ponderado. Arma la matriz de transicion M=[[k,l],[1,0]] y usa exponenciacion rapida
# de matrices (mat_pow) para obtener f(m) en O(log m) modulo 10^6, ya que N puede ser hasta
# 10^15.

def mat_mult(A, B, MOD):
    return [
        [(A[0][0]*B[0][0] + A[0][1]*B[1][0]) % MOD,
         (A[0][0]*B[0][1] + A[0][1]*B[1][1]) % MOD],
        [(A[1][0]*B[0][0] + A[1][1]*B[1][0]) % MOD,
         (A[1][0]*B[0][1] + A[1][1]*B[1][1]) % MOD],
    ]
 
def mat_pow(M, p, MOD):
    R = [[1, 0], [0, 1]]  # identidad
    while p > 0:
        if p & 1:
            R = mat_mult(R, M, MOD)
        M = mat_mult(M, M, MOD)
        p >>= 1
    return R
 
n, k, l = map(int, input().split())
MOD = 1000000
m = n // 5
 
M = [[k % MOD, l % MOD], [1, 0]]
P = mat_pow(M, m, MOD)
# f(m) = P[1][0]*f(1) + P[1][1]*f(0) = P[1][0]*k + P[1][1]
res = (P[1][0] * (k % MOD) + P[1][1]) % MOD
print(f"{res:06d}")
# <3
# Tema: LeetCode Hub / Repeticiones Consecutivas
# Resumen: El mayor k tal que word repetido k veces esta dentro de sequence
# O: (n^2 / |word|) por los hash de cada posicion
# Detalle: LeetCode 1668 "Maximum Repeating Substring": el mayor k tal que word repetido k veces
# esta dentro de sequence. Tecnica: desde cada posicion se prueba word*1, word*2, ... hasta que
# no calce. OJO: compara con hash() en vez de comparar las cadenas directamente. hash() de
# Python puede coincidir para cadenas distintas, asi que es una comparacion con riesgo y no
# aporta velocidad porque igual construye el string. Con == es mas corto y mas seguro.

class Solution:
    def maxRepeating(self, sequence: str, word: str) -> int:
        ca = []
        i = 0
        while i<len(sequence):
            try:
                j = 1
                c=0
                while True:
                    k = word*j
                    val = hash(k)        
                    s = hash(sequence[i:i+len(k)])
                    if(s == val):
                        c+=1
                    else:
                        break
                    j+=1
                ca.append(c)
            except:
                break
            i+=1
        return max(ca)
        
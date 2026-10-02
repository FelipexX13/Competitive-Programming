# <3
# Tema: LeetCode Hub / Simulacion con los Dos Mayores
# Resumen: Choque de las dos piedras mas pesadas hasta que quede una
# O: (n^2): cada max() y cada remove() recorren; con heap seria (n log n)
# Detalle: LeetCode 1046 "Last Stone Weight": choque de las dos piedras mas pesadas hasta que
# quede una. Tecnica: max() y remove() en un while. Es O(n^2) porque cada max recorre todo. Es
# el ejercicio de HEAP MAXIMO: con heapq y los valores negados, cada choque cuesta O(log n) y el
# total queda O(n log n). Ver heap/0373 en esta misma carpeta para ese truco del signo.

class Solution:
    def lastStoneWeight(self, stones: List[int]) -> int:
        while (len(stones)>1):
            ma1 = max(stones)
            stones.remove(ma1)
            ma2 = max(stones)
            stones.remove(ma2)
            if(ma1==ma2):
                continue
            else:
                stones.append(abs(ma1-ma2))
        if(len(stones)==0):
            return 0
        else:
            return stones[0]
        
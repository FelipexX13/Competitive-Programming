# <3
# Tema: LeetCode Hub / Interseccion de Prefijos
# Resumen: Para cada i, cuantos valores estan en los primeros i+1 de las dos permutaciones
# O: (n^2) por rehacer los sets; incremental seria (n)
# Detalle: LeetCode 2657 "Find the Prefix Common Array of Two Arrays": para cada i, cuantos
# valores estan en los primeros i+1 de las dos permutaciones. Tecnica: reconstruye los dos sets
# en cada paso y los cruza, o sea O(n^2). Incremental es O(n): se mantienen dos sets que van
# creciendo y en cada paso solo se revisa si el valor nuevo de A ya estaba en B (y al
# contrario). Reconstruir en vez de actualizar es el error tipico de este tipo de problema.

class Solution:
    def findThePrefixCommonArray(self, A: List[int], B: List[int]) -> List[int]:
        i = 0
        c = []
        cont = 0
        while i < len(A):
            set1 = set(A[0:i+1])
            set2 = set(B[0:i+1])
            cont = 0
            for j in set1:
                if(j in set2):
                    cont+= 1
            c.append(cont)
            i+=1
        return c
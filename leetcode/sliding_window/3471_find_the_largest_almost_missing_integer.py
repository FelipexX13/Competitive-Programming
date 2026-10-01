# <3
# Tema: LeetCode Hub / Contar en Cuantas Ventanas Aparece
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 3471 "Find the Largest Almost Missing Integer": el mayor valor que aparece en
# exactamente UNA de las ventanas de tamano k. Tecnica: para cada ventana se saca el set de sus
# valores y se cuenta en cuantas ventanas aparece cada uno; despues se toma el maximo de los que
# dan 1. El set por ventana es lo que evita contar dos veces un valor repetido dentro de la
# misma ventana. Es O(n*k) por rehacer el set en cada paso; con un diccionario incremental seria
# O(n).

class Solution:
    def largestInteger(self, nums: List[int], k: int) -> int:
        lista = {}
        i = 0
        while i<(len(nums)-k+1):
            ka = list(set(nums[i:i+k]))
            for j in ka:
                if(j in lista):
                    lista[j]+=1
                else:
                    lista[j]=1
            i+=1
        unicos = []
        for clave,valor in lista.items():
            if(valor == 1):
                unicos.append(clave)
        if(len(unicos)==0):
            return -1
        return max(unicos)
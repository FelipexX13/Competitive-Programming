# <3
# Tema: LeetCode Hub / Deshacer el Proceso al Reves
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n log n log(maximo)) por el modulo que salta varias restas de golpe
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 1354 "Construct Target Array With Multiple Sums": desde un arreglo de unos, cada paso
# reemplaza un elemento por la suma total; decir si se llega al objetivo. Tecnica: ir AL REVES.
# El mayor del arreglo tuvo que ser el ultimo escrito, asi que antes valia mayor - (suma del
# resto); con un heap maximo se devuelve ese paso y se repite. El modulo evita hacer las restas
# una por una cuando el resto es pequeno. OJO: deja un print de depuracion adentro del ciclo y
# varios cortes ad hoc.

import heapq
class Solution:
    def isPossible(self, target: List[int]) -> bool:
        tam = []
        for i in target:
            heapq.heappush(tam, i*-1)  

        if(len(target) == 1 and 1 in target):
            return True
        elif(len(target) == 1 and 1 not in target):
            return False

        cantidad = 0
        suma = sum(tam)
        ant = tam.copy()
        while cantidad != len(target): 
            mayor = heapq.heappop(tam) 
            suma -= mayor
            if(mayor == suma):
                break
            me = (-mayor) % (-suma)
            if(me == 0):
                me = -suma
            elif(me < 0):
                break
            heapq.heappush(tam, me*-1)
            cantidad = tam.count(-1)
            print(mayor, suma, me, tam, ant)
            suma -= me
            if(tam == ant):
                break
            ant = tam.copy()

        if(cantidad != len(target)):
            return  False
        else:
            return True


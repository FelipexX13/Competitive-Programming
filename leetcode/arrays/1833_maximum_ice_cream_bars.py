# <3
# Tema: LeetCode Hub / Greedy del mas Barato Primero
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 1833 "Maximum Ice Cream Bars": cuantos helados se pueden comprar con las monedas.
# Tecnica: ordenar por precio y comprar del mas barato hasta que no alcance. Es el greedy
# correcto porque todos los helados valen lo mismo para la respuesta (solo cuenta la cantidad).

class Solution:
    def maxIceCream(self, costs: List[int], coins: int) -> int:
        s = sorted(costs)
        c = 0
        cant = 0
        for i in s:
            c+=i
            if(c > coins):
                break
            
            
            cant+=1
        return cant 
        
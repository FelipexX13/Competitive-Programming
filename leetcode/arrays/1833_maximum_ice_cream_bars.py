# <3
# Tema: LeetCode Hub / Greedy del mas Barato Primero
# Resumen: Cuantos helados se pueden comprar con las monedas
# O: (n log n) por el sort, que es lo que ordena el greedy
# Detalle: LeetCode 1833 "Maximum Ice Cream Bars": cuantos helados se pueden comprar con las
# monedas. Tecnica: ordenar por precio y comprar del mas barato hasta que no alcance. Es el
# greedy correcto porque todos los helados valen lo mismo para la respuesta (solo cuenta la
# cantidad).

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
        
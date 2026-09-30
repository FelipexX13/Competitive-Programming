# <3
# Tema: LeetCode Hub / Greedy de Tercias
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 2144 "Minimum Cost of Buying Candies With Discount": por cada dos dulces comprados, el
# tercero (mas barato de los tres) es gratis.
# Tecnica: ordenar y recorrer DE MAYOR A MENOR pagando dos y saltando el tercero. Asi el regalo
# siempre cae en el dulce mas caro posible, que es lo que minimiza el total.
# El contador t es el que lleva la cuenta de dos pagados, uno gratis.

class Solution:
    def minimumCost(self, cost: List[int]) -> int:
        cost = sorted(cost)
        c = 0
        i = len(cost)-1
        t = 0
        while i>=0:
            if t==2:
                t=0
                i-=1
                continue
            c+=cost[i]
            t += 1
            i-=1
        return(c)
            
            
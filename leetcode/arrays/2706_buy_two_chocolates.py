# <3
# Tema: LeetCode Hub / Los Dos mas Baratos
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n^2) generando todos los pares; con los dos minimos seria (n)
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 2706 "Buy Two Chocolates": comprar dos chocolates sin quedar en rojo, devolviendo lo
# que sobra. Tecnica: genera todas las parejas y toma la suma minima, O(n^2). Basta con los dos
# precios mas pequenos, que salen en una sola pasada. La pareja mas barata siempre son los dos
# minimos.

class Solution:
    def buyChoco(self, prices: List[int], money: int) -> int:
        val = []
        for i in range(0,len(prices)):
            for j in range(i+1, len(prices)):
                val.append(prices[i]+prices[j])
        minimo = min(val)
        if(minimo>money):
            return money
        else:
            return money-minimo
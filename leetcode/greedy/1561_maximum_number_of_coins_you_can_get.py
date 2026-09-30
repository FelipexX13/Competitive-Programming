# <3
# Tema: LeetCode Hub / Greedy sobre Ordenado
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 1561 "Maximum Number of Coins You Can Get": se reparten los montones en tercias y de
# cada tercia uno se queda con el del medio; maximizar lo propio.
# Tecnica: ordenar y de cada tercia botar el mas grande (se lo lleva Alice), tomar el segundo
# mas grande y botar el mas pequeno (se lo lleva Bob). Los pop() desde los dos extremos son
# exactamente eso.

class Solution:
    def maxCoins(self, piles: List[int]) -> int:
        k = sorted(piles)
        c = 0
        while len(k)>0:
            k.pop()
            c += k[len(k)-1]
            k.pop(0)
            k.pop()
        return c

        
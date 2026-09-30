# <3
# Tema: LeetCode Hub / Siguiente Menor o Igual
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 1475 "Final Prices With a Special Discount in a Shop": a cada precio se le resta el
# primer precio posterior que sea menor o igual.
# Tecnica: busqueda hacia adelante, O(n^2). Con n hasta 500 pasa.
# Es otra vez el patron de pila monotona (siguiente menor), que lo dejaria en O(n). Vale la pena
# reconocerlo: cuando el enunciado dice el PRIMER elemento a la derecha que cumple algo, es pila.

class Solution:
    def finalPrices(self, prices: List[int]) -> List[int]:
        fi = []
        i = 0
        while i < len(prices)-1:
            j = i+1
            a = len(fi)
            while j<len(prices):
                if(prices[j]<=prices[i]):
                    fi.append(prices[i]-prices[j])
                    break
                j+=1
            if(a == len(fi)):
                fi.append(prices[i])
            i+=1

        fi.append(prices[i])
        return fi
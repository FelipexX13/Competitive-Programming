# <3
# Tema: LeetCode Hub / Sumar Uno a un Numero por Digitos
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (L^2) con L digitos, por el 10**c que se recalcula en cada paso
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 66 "Plus One": sumar 1 a un numero dado como arreglo de digitos. Tecnica: aca arma el
# entero completo multiplicando por potencias de 10, le suma 1 y lo vuelve a partir en digitos.
# En Python funciona porque los enteros son de tamano ilimitado. En C++ o Java esto se desborda
# y hay que hacerlo con acarreo de atras hacia adelante; ese es el metodo que vale la pena tener
# presente.

class Solution:
    def plusOne(self, digits: List[int]) -> List[int]:
        c = len(digits)-1
        v = 0
        for i in digits:
            v+= (i*10**c)
            c-=1
        v+=1
        va = str(v)
        l = []
        for i in va:
            l.append(int(i))
        return l
        
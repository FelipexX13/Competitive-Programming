# <3
# Tema: LeetCode Hub / Simulacion de Pila
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n)
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 1441 "Build an Array With Stack Operations": la lista de Push y Pop para construir el
# arreglo objetivo leyendo 1, 2, 3, ... n. Tecnica: recorrer de 1 a n haciendo Push siempre, y
# si el numero no esta en el objetivo, inmediatamente un Pop. El set es solo para consultar en
# O(1). OJO: deja un print(g) al inicio.

class Solution:
    def buildArray(self, target: List[int], n: int) -> List[str]:
        g = set(target)
        print(g)
        res = []
        num = []
        for i in range(1,n+1):
            if(target == num):
                return res
            res.append("Push")
            num.append(i)
            if(i not in g):
                res.append("Pop")
                num = num[0:len(num)-1]
        return res
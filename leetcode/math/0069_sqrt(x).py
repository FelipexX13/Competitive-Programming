# <3
# Tema: LeetCode Hub / Raiz Entera
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 69 "Sqrt(x)": la parte entera de la raiz cuadrada, sin usar sqrt.
# Tecnica: probar i = 0, 1, 2, ... hasta que i*i pase de x. Es O(raiz de x), suficiente aqui.
# Con busqueda binaria entre 0 y x queda en O(log x), que es la version que uno quiere si el
# limite sube. Cuidado con sqrt() de punto flotante, que en los bordes se equivoca en 1.

class Solution:
    def mySqrt(self, x: int) -> int:
        for i in range(x//2+2):
            k = i*i
            if(k>x):
                return i-1
            elif(k==x):
                return i
            else:
                continue
        return 1
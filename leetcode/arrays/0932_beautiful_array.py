# <3
# Tema: LeetCode Hub / Construccion Divide y Conquista
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 932 "Beautiful Array": una permutacion de 1 a n donde nunca haya i < k < j con
# arr[k]*2 == arr[i]+arr[j].
# Tecnica: construccion recursiva. Si un arreglo sirve para n/2, entonces poniendo todos los
# IMPARES (2x-1) antes de todos los PARES (2x) tambien sirve, porque impar + par nunca da un numero
# par al doble, asi que ningun trio a caballo entre los dos bloques puede fallar.
# Es el tipo de problema donde no hay busqueda, solo una construccion que se demuestra.

class Solution:
    def beautifulArray(self, n: int) -> list[int]:

        if n == 1:
            return [1]

        arr = self.beautifulArray((n + 1) // 2)

        impares = []
        pares = []

        for x in arr:
            if 2 * x - 1 <= n:
                impares.append(2 * x - 1)

            if 2 * x <= n:
                pares.append(2 * x)

        return impares + pares
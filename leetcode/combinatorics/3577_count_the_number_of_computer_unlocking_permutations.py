# <3
# Tema: LeetCode Hub / Factorial con un Filtro
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n) para el filtro, mas el factorial
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 3577 "Count the Number of Computer Unlocking Permutations": en cuantos ordenes se
# pueden desbloquear todos los computadores. Tecnica: si el primero no es el de complejidad
# ESTRICTAMENTE menor, no hay ninguna forma y la respuesta es 0. Si si, los otros n-1 van en
# cualquier orden, o sea (n-1)! mod 1e9+7. Todo el problema es darse cuenta de que solo importa
# el minimo.

class Solution(object):
    def countPermutations(self, complexity):
        import math
        menor = complexity[0]
        for i in range(1,len(complexity)):
            if(menor>= complexity[i]):
                return 0
        return math.factorial(len(complexity)-1)%((10**9)+7)
        
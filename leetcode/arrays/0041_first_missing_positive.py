# <3
# Tema: LeetCode Hub / Primer Positivo Faltante
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 41 "First Missing Positive": el menor entero positivo que no esta en el arreglo.
# Tecnica: set con todos los valores y probar 1, 2, 3, ... hasta que falte uno. OJO: el problema
# pide O(1) de memoria extra y esto usa O(n). La version buena usa el ARREGLO como marca: se
# manda cada valor v que este entre 1 y n a la posicion v-1, y al final el primer indice i donde
# nums[i] != i+1 es la respuesta. La respuesta siempre esta entre 1 y n+1, y eso es lo que hace
# que el truco funcione.

class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        n = set(nums)
        ma = max(nums)
        if(ma<1):
            return 1
        for i in range(1, ma):
            if(i in n):
                continue
            else:
                return i
        return ma+1
        
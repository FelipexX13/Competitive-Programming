# <3
# Tema: LeetCode Hub / Anagrama por Orden
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 242 "Valid Anagram": decir si dos cadenas son anagramas.
# Tecnica: ordenar las dos y comparar. Es O(n log n); con un Counter o un arreglo de 26
# frecuencias queda en O(n), que es lo que uno usaria si n fuera grande.

class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        s = list(s)
        t = list(t)
        s.sort()
        t.sort()
        if(s == t):
            return True
        else:
            return False
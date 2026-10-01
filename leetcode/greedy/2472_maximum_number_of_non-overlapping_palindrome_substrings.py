# <3
# Tema: LeetCode Hub / Greedy de Izquierda a Derecha
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 2472 "Maximum Number of Non-overlapping Palindrome Substrings": maximo de palindromos
# de largo al menos k que no se traslapen. Tecnica: solo hace falta probar longitudes k y k+1.
# Cualquier palindromo mas largo contiene uno de esas dos longitudes en el centro, y tomar el
# mas corto siempre deja mas espacio a la derecha. Con eso el greedy de tomar el primero que
# aparezca es optimo.

class Solution:
    def maxPalindromes(self, s: str, k: int) -> int:
        n = len(s)
        if k == 1: return n

        res = i = 0

        while i <= n - k:
            for d in (k, k + 1):
                if i + d <= n and s[i : i + d] == s[i : i + d][::-1]:
                    res += 1
                    i += d
                    break
            else:
                i += 1

        return res
# <3
# Tema: LeetCode Hub / Split
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 58 "Length of Last Word": el largo de la ultima palabra. Tecnica: split() sin
# argumentos ya ignora los espacios de sobra, asi que basta len(l[-1]).

class Solution:
    def lengthOfLastWord(self, s: str) -> int:
        l = s.split()
        return len(l[-1])
        
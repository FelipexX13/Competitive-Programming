# <3
# Tema: LeetCode Hub / Split
# Resumen: El largo de la ultima palabra
# O: (n) por el split
# Detalle: LeetCode 58 "Length of Last Word": el largo de la ultima palabra. Tecnica: split()
# sin argumentos ya ignora los espacios de sobra, asi que basta len(l[-1]).

class Solution:
    def lengthOfLastWord(self, s: str) -> int:
        l = s.split()
        return len(l[-1])
        
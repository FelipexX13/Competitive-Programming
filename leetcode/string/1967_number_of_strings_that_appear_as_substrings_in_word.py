# <3
# Tema: LeetCode Hub / Contar Subcadenas
# Resumen: Cuantos patrones aparecen en la palabra
# O: (patrones * |word|)
# Detalle: LeetCode 1967 "Number of Strings That Appear as Substrings in Word": cuantos patrones
# aparecen en la palabra. Tecnica: el operador in de Python sobre cada patron. Dos lineas.

class Solution:
    def numOfStrings(self, patterns: List[str], word: str) -> int:
        c=0
        for i in patterns:
            if(i in word):
                c+=1
        return c
            
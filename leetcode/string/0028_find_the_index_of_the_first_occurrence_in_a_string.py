# <3
# Tema: LeetCode Hub / Busqueda de Subcadena
# Resumen: La posicion de la primera aparicion de needle en haystack
# O: (n*m) el find de Python en el peor caso; con KMP es (n+m)
# Detalle: LeetCode 28 "Find the Index of the First Occurrence in a String": la posicion de la
# primera aparicion de needle en haystack. Tecnica: haystack.index(needle) y listo. Sirve como
# recordatorio de que en Python la busqueda de subcadena viene de fabrica; en C++ es s.find(t).
# Si pidieran hacerlo a mano, es KMP, que esta en el notebook.

class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        try:
            p = haystack.index(needle)
            return p
        except:
            return -1
        
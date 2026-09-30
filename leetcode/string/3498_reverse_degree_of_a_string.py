# <3
# Tema: LeetCode Hub / Suma Ponderada
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 3498 "Reverse Degree of a String": sumar, por cada letra, su posicion invertida en el
# alfabeto (a vale 26, z vale 1) por su posicion en la cadena.
# Tecnica: diccionario con los 26 valores y un solo ciclo. El valor invertido tambien sale con
# 27 - (ord(c) - ord('a') + 1), sin escribir la tabla.

class Solution:
    def reverseDegree(self, s: str) -> int:
        le = {
            "a": 26, "b": 25, "c": 24, "d": 23, "e": 22, "f": 21,
            "g": 20, "h": 19, "i": 18, "j": 17, "k": 16, "l": 15,
            "m": 14, "n": 13, "o": 12, "p": 11, "q": 10, "r": 9,
            "s": 8, "t": 7, "u": 6, "v": 5, "w": 4, "x": 3, "y": 2,
            "z": 1
        }

        #s = s[::-1]
        suma = 0
        for i in range(len(s)):
            suma += (le[s[i]]*(i+1))

        return suma
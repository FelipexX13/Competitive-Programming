# <3
# Tema: LeetCode Hub / Sets de Letras
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 3120 "Count the Number of Special Characters I": cuantas letras aparecen en minuscula
# y tambien en mayuscula. Tecnica: un set con todos los caracteres y para cada minuscula se
# pregunta si su upper() tambien esta. Dos lineas.

class Solution:
    def numberOfSpecialChars(self, word: str) -> int:

        w = set(word)
        c = 0
        for i in w:
            if(i.islower() and i.upper() in w ):
                c+=1
        return c
        
        
# <3
# Tema: LeetCode Hub / Palindromo con Dos Punteros
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 9 "Palindrome Number": decir si un entero se lee igual al reves.
# Tecnica: pasarlo a string y comparar el caracter i con el de la otra punta hasta la mitad.
# OJO: los negativos nunca son palindromos por el signo, y aca el '-' se compara como un
# caracter mas, asi que -121 da False por casualidad y no por la regla.

class Solution:
    def isPalindrome(self, x: int) -> bool:
        b = str(x)
        i = 0
        while i < len(b)/2:
            if(b[i]==b[len(b)-1-i]):
                i+=1
                continue
            else:
                return False
        return True
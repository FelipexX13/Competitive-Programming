# <3
# Tema: LeetCode Hub / Casos de Mayusculas
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n), compara contra upper() y lower()
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 520 "Detect Capital": decir si el uso de mayusculas es valido (todas, ninguna, o solo
# la primera). Tecnica: comparar la palabra contra su upper() y su lower(); si coincide con
# alguno, listo. El tercer caso es primera en mayuscula y ninguna otra. En Python los tres casos
# son word.isupper() or word.islower() or word.istitle().

class Solution:
    def detectCapitalUse(self, word: str) -> bool:
        gr = word.upper()
        pe = word.lower()
        if(word == gr):
            return True
        elif(word == pe):
            return True
        else:
            if(word[0] == word[0].upper()):
                c = 0
                for i in range(1,len(word)):
                    if(word[i] == word[i].upper()):
                        c+=1
                if(c == 0):
                    return True
            return False
            
        
# <3
# Tema: LeetCode Hub / Rotacion de Cadena
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 796 "Rotate String": decir si goal es una rotacion de s.
# Tecnica: para cada posicion donde aparece la primera letra de goal, se compara dando la vuelta
# con el modulo (el k = 0 cuando se pasa del final).
# El truco de una linea: goal esta en s+s si y solo si es una rotacion. Y si hay que hacerlo
# rapido para cadenas grandes, es KMP sobre s+s.

class Solution:
    def rotateString(self, s: str, goal: str) -> bool:
        if(len(s)!=len(goal)):
            return False
        
        inicio = goal[0]

        for i in range(len(s)):
            if(s[i] == inicio):
                j = 1
                k = i+1
                f = True
                while j<len(goal):
                    if(k>=len(s)):
                        k=0
                    if(goal[j]!=s[k]):
                        f = False
                        break
                    j+=1
                    k+=1
                if(f):
                    return True
        return False
# <3
# Tema: LeetCode Hub / Sustitucion de Plantilla
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 1807 "Evaluate the Bracket Pairs of a String": reemplazar cada (clave) por su valor, o
# por ? si no se conoce.
# Tecnica: diccionario con el conocimiento y un barrido que al ver un parentesis lee hasta el
# cierre y sustituye. Un solo recorrido, O(n).

class Solution:
    def evaluate(self, s: str, knowledge: list[list[str]]) -> str:
        dic = {}
        for i in knowledge:
            dic[i[0]] = i[1]
        res = ""
        i=0
        while i < len(s):
            if(s[i]=="("):
                ini = i+1
                fin = i+2
                pal = s[ini]
                while (s[fin] != ")"):
                    pal += s[fin]
                    fin += 1
                if(pal in dic):
                    res += dic[pal]
                else: 
                    res += "?"
                i = fin
            else:
                res+= s[i]
            i+=1
        return res

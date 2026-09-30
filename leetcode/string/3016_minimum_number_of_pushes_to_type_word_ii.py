# <3
# Tema: LeetCode Hub / Greedy por Frecuencia
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 3016 "Minimum Number of Pushes to Type Word II": lo mismo pero con letras repetidas.
# Tecnica: ahora SI importa el orden. Se cuentan frecuencias, se ordena de mayor a menor y se les
# va dando el costo 1 a las 8 mas frecuentes, 2 a las 8 siguientes, etc. Es el greedy de darle la
# posicion barata a lo que mas se usa, la misma idea que Huffman.
# La diferencia con la version I es exactamente ese sorted por frecuencia.

class Solution:
    def minimumPushes(self, word: str) -> int:
        dic = {}
        for i in word:
            if(i in dic):
                dic[i]+= 1
            else:
                dic[i] = 1

        va  = 1
        c = 0
        t = 0
        dic = dict(sorted(dic.items(), key=lambda item: item[1], reverse=True))
        for clave,valor in dic.items():
            t += 1
            if(t > 8):
                t=1
                va +=1
            c += (valor*va)
            
        return c



        
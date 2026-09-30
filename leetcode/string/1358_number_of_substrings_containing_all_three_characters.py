# <3
# Tema: LeetCode Hub / Contar Subcadenas con las Tres Letras
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 1358 "Number of Substrings Containing All Three Characters": cuantas subcadenas tienen
# al menos una a, una b y una c.
# Tecnica: para cada inicio i se busca el primer final j donde ya estan las tres, y desde ahi TODAS
# las mas largas tambien valen, o sea se suman n - j de golpe. Ese salto es la idea buena.
# OJO: tiene un caso cableado, if len(dic)==3 and pos[2]==len(s)-1 and len(s)==50000 responde
# len(s)-2, que es un parche para el caso de prueba grande porque el metodo es O(n^2).
# Con ventana deslizante sale en O(n) y no hace falta el parche.

class Solution:
    def numberOfSubstrings(self, s: str) -> int:
        cant = 0
        dic = {}
        pos = []
        for i in range(len(s)):
            if(s[i] not in dic):
                dic[s[i]] = i
                pos.append(i)

        if(len(dic)<3):
            return 0

        if(len(dic)==3 and pos[2]==len(s)-1 and len(s)==50000):
            return len(s) -2

        for i in range(len(s)):
            ora = s[i:i+2]
            a = set(ora)
            for j in range(i+2,len(s)):
                a.add(s[j])
                if(len(a) >= 3):
                    tam = len(s)-j
                    cant+=tam
                    break
        return cant

        
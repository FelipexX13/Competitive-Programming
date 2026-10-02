# <3
# Tema: LeetCode Hub / Conteo de Desplazamientos
# Resumen: Deslizando una imagen binaria sobre otra, maximo de unos que se superponen
# O: (u1*u2) con u = cantidad de unos; peor caso (n^4)
# Detalle: LeetCode 835 "Image Overlap": deslizando una imagen binaria sobre otra, maximo de
# unos que se superponen. Tecnica: en vez de probar cada traslacion, se saca la lista de
# posiciones con 1 de cada imagen y para cada par se anota el desplazamiento (dr, dc) en un
# diccionario. El desplazamiento que mas veces aparece ES la respuesta. O(u1*u2) con u =
# cantidad de unos.

class Solution:
    def largestOverlap(self, img1, img2):
        n = len(img1)

        ones1 = [(r, c) for r in range(n) for c in range(n) if img1[r][c] == 1]
        ones2 = [(r, c) for r in range(n) for c in range(n) if img2[r][c] == 1]

        frequency = {}
        maxOverlap = 0

        for r1, c1 in ones1:
            for r2, c2 in ones2:
                dr = r1 - r2
                dc = c1 - c2

                key = (dr, dc)
                frequency[key] = frequency.get(key, 0) + 1
                maxOverlap = max(maxOverlap, frequency[key])

        return maxOverlap
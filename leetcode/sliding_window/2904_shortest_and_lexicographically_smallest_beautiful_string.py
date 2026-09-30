# <3
# Tema: LeetCode Hub / Ventana con Conteo Exacto
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 2904 "Shortest and Lexicographically Smallest Beautiful String": la subcadena mas
# corta con exactamente k unos, y entre las de ese largo la menor alfabeticamente.
# Tecnica: ventana deslizante que crece por la derecha y en cuanto tiene k unos se encoge por la
# izquierda guardando todas las de largo minimo. Al final un min() sobre las candidatas resuelve
# el desempate lexicografico.
# Guardar los rangos y no las cadenas evita cortar strings dentro del ciclo.

class Solution:
    def shortestBeautifulSubstring(self, s: str, k: int) -> str:
        if len(s) == 0:
            return ""
    

        inicio = 0
        fin = 0
        cont = 0
        resp = []
        menor = 99999999999999

        while fin < len(s):

            if s[fin] == "1":
                cont += 1

            while cont == k:

                tam = fin - inicio + 1

                if tam < menor:
                    menor = tam
                    resp = [[inicio, fin]]

                elif tam == menor:
                    resp.append([inicio, fin])

                if s[inicio] == "1":
                    cont -= 1

                inicio += 1

            fin += 1

        if len(resp) == 0:
            return ""

        r = []

        for i in resp:
            r.append(s[i[0]:i[1] + 1])

        return min(r)
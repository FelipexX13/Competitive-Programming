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
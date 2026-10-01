# <3
# Tema: LeetCode Hub / Expansion Recursiva de Llaves
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 1096 "Brace Expansion II": expandir una expresion con llaves y comas anidadas.
# Tecnica: se busca la PRIMERA llave que cierra y su llave que abre mas cercana hacia atras
# (rfind). Eso aisla el grupo mas interno, se reemplaza por cada opcion separada por comas y se
# vuelve a llamar. El set junta y quita duplicados y el sorted ordena al final. Atacar siempre
# el grupo mas interno es lo que hace que la recursion sea tan corta.

class Solution:
    def braceExpansionII(self, expression):
        ans = set()

        def dfs(s):
            r = s.find('}')

            # No braces left
            if r == -1:
                ans.add(s)
                return

            # Find matching '{'
            l = s.rfind('{', 0, r)

            left = s[:l]
            right = s[r + 1:]

            # Content inside { }
            inside = s[l + 1:r]

            for part in inside.split(','):
                dfs(left + part + right)

        dfs(expression)
        return sorted(ans)

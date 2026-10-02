# <3
# Tema: LeetCode Hub / Pila Monotona Lexicografica
# Resumen: Dejar una sola copia de cada letra y que el resultado sea el lexicograficamente menor
# O: (n), cada letra entra y sale de la pila una vez
# Detalle: LeetCode 316 "Remove Duplicate Letters": dejar una sola copia de cada letra y que el
# resultado sea el lexicograficamente menor. Tecnica: pila monotona con dos apoyos, un Counter
# de lo que FALTA por ver y un set de lo que ya esta en la pila. Se saca de la pila mientras la
# cima sea mayor que la letra actual Y todavia quede otra copia de esa cima mas adelante. Ese
# conteo de lo que falta es la clave. Es el molde de todos los problemas de subsecuencia
# lexicograficamente minima.

from collections import Counter

class Solution:
    def removeDuplicateLetters(self, s: str) -> str:

        count = Counter(s)
        stack = []
        seen = set()

        for c in s:

            count[c] -= 1

            if c in seen:
                continue

            while (
                stack and
                c < stack[-1] and
                count[stack[-1]] > 0
            ):
                seen.remove(stack.pop())

            stack.append(c)
            seen.add(c)

        return "".join(stack)
# <3
# Tema: LeetCode Hub / Pila de Parentesis con Reverso
# Resumen: Invertir lo que hay dentro de cada par de parentesis, respetando el anidamiento
# O: (n^2): cada cierre reconstruye la cadena entera
# Detalle: LeetCode 1190 "Reverse Substrings Between Each Pair of Parentheses": invertir lo que
# hay dentro de cada par de parentesis, respetando el anidamiento. Tecnica: pila con las
# posiciones de los parentesis que abren. Al encontrar uno que cierra se invierte el pedazo de
# adentro y se reescribe la cadena sin los parentesis. El i -= 2 es para reacomodar el indice
# despues de que la cadena se acorto en dos caracteres. Modificar la cadena adentro del ciclo es
# lo delicado; con una pila de STRINGS acumulados no hay que tocar indices.

class Solution:
    def reverseParentheses(self, s: str) -> str:
        stack = []
        i = 0
        while i< len(s):
            if(s[i]=="("):
                stack.append(i)
            elif(s[i]==")"):
                pal = s[stack[-1]+1:i]
                pal = pal[::-1]
                ini = s[:stack[-1]]
                fin = s[i+1:]
                s = ini+pal+fin
                stack.pop()
                i-=2
            i+=1
        return s
                
                

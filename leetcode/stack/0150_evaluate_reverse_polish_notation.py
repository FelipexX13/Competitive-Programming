# <3
# Tema: LeetCode Hub / Evaluacion en Notacion Polaca
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 150 "Evaluate Reverse Polish Notation": evaluar una expresion en notacion postfija.
# Tecnica: pila de numeros. Si el token es numero se empuja; si es operador se sacan los DOS de
# arriba, se opera y se devuelve el resultado. Al final queda uno solo. El orden importa,
# lit[-2] es el izquierdo y lit[-1] el derecho. La division usa int(a/b) y no a//b porque el
# problema pide truncar hacia cero y // de Python redondea hacia abajo.

class Solution:
    def evalRPN(self, tokens: List[str]) -> int:
        lit = []
        ope = set(["+","-","*","/"])
        for i in range(len(tokens)):
            if(tokens[i] not in ope):
                lit.append(int(tokens[i]))
            else:
                if(tokens[i]=="+"):
                    v = lit[-2]+lit[-1]
                    lit = lit[0:len(lit)-2]
                    lit.append(v)
                elif(tokens[i]=="-"):
                    v = lit[-2]-lit[-1]
                    lit = lit[0:len(lit)-2]
                    lit.append(v)
                elif(tokens[i]=="*"):
                    v = lit[-2]*lit[-1]
                    lit = lit[0:len(lit)-2]
                    lit.append(v)
                elif(tokens[i]=="/"):
                    v = int(lit[-2]/lit[-1])
                    lit = lit[0:len(lit)-2]
                    lit.append(v)
        return lit[0]
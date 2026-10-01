# <3
# Tema: LeetCode Hub / Frecuencia de Digitos
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 3945 "Digit Frequency Score": sumar cada digito multiplicado por cuantas veces
# aparece. Tecnica: diccionario de frecuencias sobre los caracteres y suma de digito por
# frecuencia. OJO: reusa el nombre v para el numero y para el valor del diccionario. No rompe
# nada porque el primero ya no se usa, pero es de esas cosas que en un problema mas largo si
# muerden.

class Solution:
    def digitFrequencyScore(self, n: int) -> int:
        v = str(n)
        dicc = {}
        for i in v:
            if(i in dicc):
                dicc[i]+=1
            else:
                dicc[i]=1
        value = 0
        for c,v in dicc.items():
            value += (int(c)*v)

        return value
            
        
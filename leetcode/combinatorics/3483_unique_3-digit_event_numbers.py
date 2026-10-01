# <3
# Tema: LeetCode Hub / Conteo con Frecuencias
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (10^3 = 1000), tres ciclos sobre los digitos
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 3483 "Unique 3-Digit Event Numbers": cuantos numeros distintos de 3 cifras se pueden
# armar con los digitos dados, que sean pares y no empiecen por 0. Tecnica: arreglo de
# frecuencias y tres ciclos, uno por posicion, restando y devolviendo la frecuencia al entrar y
# salir (backtracking barato). El set al final quita los repetidos. Este mismo problema esta
# resuelto en C++ en la carpeta LeetCode del notebook.

class Solution:
    def totalNumbers(self, digits: List[int]) -> int:
        res = set()
        fre = [0]*10
        for i in digits:
            fre[i] += 1
        
        for C in range(0,10,2):
            if(fre[C]==0):
                continue
            fre[C]-=1
            for A in range(1,10):
                if(fre[A]==0):
                    continue
                fre[A]-=1
                for B in range(0,10):
                    if(fre[B]==0):
                        continue
                    res.add(int(str(A)+str(B)+str(C)))
                fre[A]+=1
            fre[C]+=1
        return len(res)
                


        
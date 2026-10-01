# <3
# Tema: LeetCode Hub / Siguiente Dia mas Caliente
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n^2) en el peor caso; con pila monotona es (n)
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 739 "Daily Temperatures": para cada dia, cuantos dias faltan para uno mas caliente.
# Tecnica del codigo: busqueda hacia adelante con un cache por temperatura, reusando el
# resultado de la vez anterior que aparecio ese mismo valor. Es ingenioso pero en el peor caso
# sigue siendo O(n^2) y cuesta leerlo. Esto es el problema de PILA MONOTONA por excelencia: se
# lleva una pila de indices con temperaturas decrecientes y cuando llega una mas alta se
# resuelven todos los de la pila que sean menores. O(n) y diez lineas. La version de pila esta
# en stack/1019 de esta misma carpeta.

class Solution:
    
    def calculo(self, temperatures, i):
        j = i+1
        c = 0
        f = False
        while j < len(temperatures):
            if(temperatures[i]>= temperatures[j]):
                c+=1
            else:
                c+=1
                f = True
                break
            j+=1
        if(f):
            return c
        else:
            return 0


    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:

        ma = max(temperatures)
        fin  = []
        dic = {}
        i = 0
        while i < len(temperatures)-1:
            if(temperatures[i]== ma):
                fin.append(0)
            elif(temperatures[i] not in dic):
                dic[temperatures[i]] = [i]
                val = self.calculo(temperatures, i)
                fin.append(val)
                dic[temperatures[i]].append(val)
            else:
                rest = (dic[temperatures[i]][1])-(i-dic[temperatures[i]][0])
                if(rest>-1):
                    dic[temperatures[i]] = [i,rest]
                    fin.append(rest)
                else:
                    val = self.calculo(temperatures, i)
                    fin.append(val)
                    dic[temperatures[i]].append(val)
            i+=1

        fin.append(0)
        return fin
        
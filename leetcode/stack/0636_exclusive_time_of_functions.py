# <3
# Tema: LeetCode Hub / Pila de Llamadas
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 636 "Exclusive Time of Functions": tiempo propio de cada funcion, sin contar lo que
# gasta en las que llama.
# Tecnica: pila con los ids de las funciones abiertas y una variable val con el instante del
# ultimo evento. En cada start se le cobra a la de la cima el tiempo transcurrido, y en cada end
# se le cobra el tramo final y se saca. El +1 y el val = fin+1 son porque los timestamps son
# unidades completas y no instantes.
# OJO: arma la respuesta recorriendo el diccionario en orden de insercion, no por id de funcion.
# Si la primera funcion que arranca no es la 0, el resultado sale en el orden equivocado.

class Solution:
    def exclusiveTime(self, n: int, logs: List[str]) -> List[int]:
        dic = {}
        val = 0
        stack = []
        for i in range(len(logs)):
            partes = logs[i].split(":")
            if(partes[1]== "start"):
                if(partes[0] not in dic):
                    dic[partes[0]]=0
                if(int(partes[2])!=val):
                    dic[stack[-1]] += int(partes[2])-val
                stack.append(partes[0])
                val = int(partes[2])
            else:
                time = int(partes[2]) - val + 1
                dic[stack[-1]] += time
                stack.pop()
                val = int(partes[2])+1
                
        f = []
        for clave,val in dic.items():
            f.append(val)

        return f


                

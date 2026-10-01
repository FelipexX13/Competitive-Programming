# <3
# Tema: LeetCode Hub / Triangulo de Pascal
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n^2), que es el tamano de la salida
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 118 "Pascal's Triangle": las primeras numRows filas del triangulo. Tecnica: cada fila
# sale de la anterior sumando vecinos, con un 1 en cada punta. Es la recurrencia C(n,k) =
# C(n-1,k-1) + C(n-1,k) construida hacia abajo, sin factoriales y sin division. Asi se construye
# la tabla de binomiales cuando hay que consultarla muchas veces.

class Solution:
    def generate(self, numRows: int) -> List[List[int]]:
        numFilas = numRows       

        matriz = []

        fila = [1]

        cont = 0                

        while cont < numFilas:
            
            matriz.append(fila)  

            nueva = [1]
            
            for i in range(len(fila) - 1):
                
                nueva.append(fila[i] + fila[i + 1])
                
            nueva.append(1)

            fila = nueva
            cont+=1
            
            

        return(matriz)



        
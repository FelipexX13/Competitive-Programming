# <3
# Tema: LeetCode Hub / Recorrido de Matriz
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n*m), un solo barrido
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 463 "Island Perimeter": perimetro de la isla dibujada con 1 en una matriz. Tecnica:
# por cada celda de tierra se cuentan sus vecinos de tierra y se aporta 4 - vecinos. No hace
# falta DFS ni marcar visitados, es un solo barrido.

class Solution(object):
    def islandPerimeter(self, grid):
        n = len(grid)
        m = len(grid[0])
        p = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if(grid[i][j]==1):
                    l = 0
                    if(i != 0 and grid[i-1][j] == 1):
                        l+=1
                    if(i != n-1 and grid[i+1][j] == 1):
                        l+=1
                    if(j != 0 and grid[i][j-1] == 1):
                        l+=1
                    if(j != m-1 and grid[i][j+1] == 1):
                        l+=1
                    if(l==0):
                        p+=4
                    elif(l==1):
                        p+=3
                    elif(l==2):
                        p+=2
                    elif(l==3):
                        p+=1
        return p
        
# <3
# Tema: LeetCode Hub / Compatibilidad de Tubos en Matriz
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n*m), DFS con visitados sobre la cuadricula
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 1391 "Check if There is a Valid Path in a Grid": una cuadricula de tubos numerados 1
# a 6; decir si se puede ir de la esquina de arriba a la de abajo. Tecnica: DFS donde moverse
# solo vale si el tubo actual apunta hacia el vecino Y el vecino apunta de vuelta. Las listas
# [1,3,5] y compania son justo los tubos que reciben por cada lado, y esa tabla de
# compatibilidad es todo el problema. Este mismo problema esta resuelto en C++ en la carpeta
# LeetCode del notebook.

class Solution:
    
    def DFS(self, i, j, grid, memo):
        if i < 0 or i >= len(grid) or j < 0 or j >= len(grid[0]):
            return False
        if (i, j) in memo:
            return False
        if i == len(grid) - 1 and j == len(grid[0]) - 1:
            return True

        memo.add((i, j))

        calle = grid[i][j]

        if calle == 1:
            nj = j + 1
            if nj < len(grid[0]) and grid[i][nj] in [1, 3, 5]:
                if self.DFS(i, nj, grid, memo):
                    return True
            nj = j - 1
            if nj >= 0 and grid[i][nj] in [1, 4, 6]:
                if self.DFS(i, nj, grid, memo):
                    return True
        elif calle == 2:

            ni = i + 1
            if ni < len(grid) and grid[ni][j] in [2, 5, 6]:
                if self.DFS(ni, j, grid, memo):
                    return True

            
            ni = i - 1
            if ni >= 0 and grid[ni][j] in [2, 3, 4]:
                if self.DFS(ni, j, grid, memo):
                    return True

        
        elif calle == 3:

            
            ni = i + 1
            if ni < len(grid) and grid[ni][j] in [2, 5, 6]:
                if self.DFS(ni, j, grid, memo):
                    return True

            
            nj = j - 1
            if nj >= 0 and grid[i][nj] in [1, 4, 6]:
                if self.DFS(i, nj, grid, memo):
                    return True

        
        elif calle == 4:

            
            nj = j + 1
            if nj < len(grid[0]) and grid[i][nj] in [1, 3, 5]:
                if self.DFS(i, nj, grid, memo):
                    return True

            
            ni = i + 1
            if ni < len(grid) and grid[ni][j] in [2, 5, 6]:
                if self.DFS(ni, j, grid, memo):
                    return True

        
        elif calle == 5:

            
            ni = i - 1
            if ni >= 0 and grid[ni][j] in [2, 3, 4]:
                if self.DFS(ni, j, grid, memo):
                    return True

        
            nj = j - 1
            if nj >= 0 and grid[i][nj] in [1, 4, 6]:
                if self.DFS(i, nj, grid, memo):
                    return True

    
        elif calle == 6:

            
            ni = i - 1
            if ni >= 0 and grid[ni][j] in [2, 3, 4]:
                if self.DFS(ni, j, grid, memo):
                    return True

            
            nj = j + 1
            if nj < len(grid[0]) and grid[i][nj] in [1, 3, 5]:
                if self.DFS(i, nj, grid, memo):
                    return True

        return False

    def hasValidPath(self, grid):
        memo = set()
        return self.DFS(0, 0, grid, memo)
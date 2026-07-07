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
class Solution:
    
    def BFS(self, grid, m, n, health, ant):
        #print(m,n,health)
        ant[str(m)+str(n)] = health
        if(health <= 0):
            return 0
        elif(m==len(grid)-1 and n==len(grid[0])-1):
            return 1
        else:
            k = [[1,0],[0,1],[-1,0],[0,-1]]
            resp = 2
            for i in k:
                #print(m,n,health, i, "-------------")
                if(m+i[0]>-1 and m+i[0]<len(grid) and n+i[1]>-1 and n+i[1]<len(grid[0]) and str(m+i[0])+str(n+i[1]) not in ant):
                    if(grid[m+i[0]][n+i[1]] == 1):
                        resp = self.BFS(grid,m+i[0],n+i[1],health-1, ant)
                    else:
                        resp = self.BFS(grid,m+i[0],n+i[1],health,ant)
                elif(m+i[0]>-1 and m+i[0]<len(grid) and n+i[1]>-1 and n+i[1]<len(grid[0]) and ant[str(m+i[0])+str(n+i[1])] < health):
                    if(grid[m+i[0]][n+i[1]] == 1):
                        resp = self.BFS(grid,m+i[0],n+i[1],health-1, ant)
                    else:
                        resp = self.BFS(grid,m+i[0],n+i[1],health,ant)
                if(resp == 1):
                    break
            if(resp == 1):
                return 1
            else:
                return 2

    def findSafeWalk(self, grid: List[List[int]], health: int) -> bool:
        unos = 0
        for i in grid:
            unos += i.count(1)
        if(unos==(len(grid[0])*len(grid)) and health<=(len(grid[0])+len(grid))-1):
            return False
        if(grid[0][0]==1):
            health-=1
        ant = {"00":health}
        res = self.BFS(grid, 0, 0, health, ant)
        if(res == 1):
            return True
        else:
            return False
        
        
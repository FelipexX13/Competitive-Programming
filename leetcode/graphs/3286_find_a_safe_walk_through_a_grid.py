# <3
# Tema: LeetCode Hub / Busqueda con Vida Restante
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 3286 "Find a Safe Walk Through a Grid": cruzar la cuadricula sin que la vida llegue a 0,
# perdiendo 1 en cada celda marcada.
# Tecnica: busqueda con el estado (celda, vida) y la poda importante: si ya se visito esa celda
# con MAS vida, volver con menos nunca sirve. Ese ant[celda] = mejor vida vista es lo que evita
# la explosion.
# OJO: la funcion se llama BFS pero es recursiva, o sea DFS, y usa str(m)+str(n) como clave, que
# confunde 1,12 con 11,2. Con cuadriculas de hasta 50x50 no choca, pero es una llave mala.
# Lo correcto es BFS 0-1 (deque) o Dijkstra sobre el estado (celda, vida).

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
        
        
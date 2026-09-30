# <3
# Tema: LeetCode Hub / Memoizacion
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 70 "Climbing Stairs": de cuantas formas se sube una escalera de n subiendo 1 o 2.
# Tecnica: Fibonacci con memoizacion, arreglo vis donde 0 significa sin calcular. Es el ejemplo
# mas corto de DP top-down: recursion normal mas una tabla que guarda lo ya hecho.
# Bottom-up con dos variables gasta O(1) de memoria.

class Solution:
    def fibo(self,n,vis):
        if(vis[n]!=0):
            return vis[n]
        if(n==0 or n==1):
            return 1
        a = self.fibo(n-1,vis)+self.fibo(n-2,vis)
        vis[n] = a
        return a

    def climbStairs(self, n: int) -> int:
        vis = [0]*(n+1)
        return self.fibo(n,vis)
        
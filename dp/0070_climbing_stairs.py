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
        
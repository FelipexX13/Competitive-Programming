class Solution:
    def magicalString(self, n: int) -> int:
        chi = 2
        cant = 1
        s = "122"
        F = True
        i = 3
        while i < n:
            if(F):
                can = int(s[chi])
                chi+=1
                so = "1"*can
                s += so
                i += can
                if(i<=n):
                    cant += can
                else:
                    cant += 1
                F= False
            else:
                can = int(s[chi])
                chi+=1
                so = "2"*can
                s += so
                i += can
                F= True

        return cant

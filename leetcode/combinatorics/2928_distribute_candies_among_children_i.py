class Solution:
    def distributeCandies(self, n: int, limit: int) -> int:
        cont = 0
        for val1 in range(limit+1):
            if(val1+2*limit < n):
                continue
            else:
                for val2 in range(limit+1):
                    if(val1+val2+limit < n or (val1==val2 and val1== n-val1-val2) or n-val1-val2 < 0):
                        continue
                    else:
                        print(val1)
                        print(val2)
                        print(n-val1-val2)
                        print("--------")
                        cont+=1
        for i in range(limit+1):
            if(i*3 == n):
                cont+=1
        return (cont)
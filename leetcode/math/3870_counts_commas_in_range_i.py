class Solution:
    def countCommas(self, n: int) -> int:
        if(len(str(n))<=3):
            return 0
        else:
            k = 1000
            c = 1
            ja = 0
            while True:
                if(n//k == 0):
                    break
                if(ja==3):
                    c+=1
                    ja = 0
                k*=10
                ja+=1
            k=1000
            return int(n-k+1)*c

            
        
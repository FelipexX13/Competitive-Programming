class Solution:
    def minimumFlips(self, n: int) -> int:
        bi = bin(n)[2:]
        bini = bi[::-1]
        cont = 0
        for i in range(len(bi)):
            if(bi[i]!=bini[i]):
                cont+=1
        return cont

        
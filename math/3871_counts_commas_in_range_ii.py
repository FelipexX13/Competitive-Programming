class Solution:
    def countCommas(self, n: int) -> int:
        cont = 0
        num = int("1"+("0"*(len(str(n))-1)))
        while num > 999:
            div = (len(str(num))-1)//3
            cont+=(n-num+1)*div
            n=num-1
            num = int("1"+("0"*(len(str(num))-2)))
        return cont
        
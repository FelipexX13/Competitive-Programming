class Solution:
    def totalWaviness(self, num1: int, num2: int) -> int:
        cont=0
        for i in range(num1,num2+1,1):
            a = str(i)
            for j in range(1,len(a)-1,1):
                if(a[j-1]< a[j] and a[j+1] < a[j]):
                    cont+=1
                elif(a[j-1]> a[j] and a[j+1] > a[j]):
                    cont+=1
        return cont
        
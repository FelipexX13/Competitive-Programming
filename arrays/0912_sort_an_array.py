class Solution:
    def sortArray(self, nums: list[int]) -> list[int]:
        mi = float("inf")
        ma = 0
        dic = {}
        for i in nums:
            if(i>ma):
                ma = i
            if(i<mi):
                mi = i
            if(i in dic):
                dic[i]+=1
            else:
                dic[i]=1
        
        fin = [0]*len(nums)
        va = 0
        for i in range(mi,ma+1):
            try:
                c = dic[i]
                for j in range(c):
                    fin[va] = i
                    va += 1
            except:
                continue
        return fin
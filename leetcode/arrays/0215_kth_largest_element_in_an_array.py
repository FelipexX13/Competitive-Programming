class Solution:
    def findKthLargest(self, nums: list[int], k: int) -> int:
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
        c = 0
        for i in range(ma,mi-1,-1):
            try:
                c += dic[i]
                if(c>=k):
                    break
            except:
                continue
        return i
        
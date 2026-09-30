class Solution:
    def waysToMakeFair(self, nums: List[int]) -> int:
        par = [0]
        sumap = 0
        impar = [0]
        sumai = 0
        for i in range(len(nums)):
            if(i%2==0):
                sumap += nums[i]
            else: 
                sumai += nums[i]
            par.append(sumap)
            impar.append(sumai)
        van = 0
        for i in range(len(nums)):
            sumap = par[i] + impar[-1] - impar[i+1]
            sumai = impar[i] + par[-1] - par[i+1]
            if(sumap == sumai):
                van += 1
        return van

        
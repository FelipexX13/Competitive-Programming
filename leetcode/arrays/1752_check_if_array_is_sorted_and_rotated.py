class Solution:
    def check(self, nums: List[int]) -> bool:
        l = sorted(nums)
        po = 0
        for k in range(len(nums)-1,-1,-1):
            #print(nums[k], l[0])
            if(nums[k]==l[0] and nums[k-1]!=l[0]):
                po = k
                break
        #print(po)
        po2 = nums.index(l[0])
        cant = 0
        f = False
        for h in range(po2,po+1):
            if(nums[h]== l[0]):
                continue
            else:
                f = True
                break
        if(f==False):
            po = po2
        else:
            po = po
        i = po
        j = 0
        flag = 0
        while (j < len(nums) and flag == 0):
            if(i==len(nums)):
                i=0
            if(nums[i] == l[j]):
                i+=1
                j+=1
                continue
            else:
                flag = 1
                break
        if(flag == 1):
            return False
        else:
            return True
        
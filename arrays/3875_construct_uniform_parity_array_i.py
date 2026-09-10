class Solution:
    def uniformArray(self, nums1: list[int]) -> bool:
        lPar = []
        lImpar = []
        for i in range(len(nums1)):
            if(nums1[i]%2==0):
                lPar.append(nums1[i])
                for j in range(len(nums1)):
                    if(i!=j and (nums1[i]-nums1[j])%2==1):
                        lImpar.append(nums1[i]-nums1[j])
                        break
            else:
                lImpar.append(nums1[i])
                for j in range(len(nums1)):
                    if(i!=j and (nums1[i]-nums1[j])%2==0):
                        lPar.append(nums1[i]-nums1[j])
                        break
        
        if(len(lPar)== len(nums1) or len(lImpar)==len(nums1)):
            return True
        else:
            return False
        
class Solution:
    def uniformArray(self, nums1: list[int]) -> bool:
        menor_par = float('inf')
        posP = 0
        menor_impar = float('inf')
        posI = 0
        pos = 0
        for x in nums1:
            if x % 2 == 0:
                if(menor_par > x):
                    menor_par = x
                    posP = pos
            else:
                if(menor_impar > x):
                    menor_impar = x
                    posI = pos
            pos+=1
        #if(menor_par == float('inf') or menor_impar == float('inf')):
        #    return False
        
        cp = 0
        ci = 0
        pos = 0
        for i in nums1:
            if(i %2 == 0):
                cp+=1
            elif(pos != posI and i-menor_impar >= 1):
                cp+=1

            if(i %2 == 1):
                ci+=1
            elif(pos != posI and i-menor_impar >= 1):
                ci+=1
            pos+=1

        if(ci == len(nums1) or cp == len(nums1)):
            return True

        return False
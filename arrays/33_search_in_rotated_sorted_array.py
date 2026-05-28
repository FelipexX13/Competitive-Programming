class Solution:
    def search(self, nums: List[int], target: int) -> int:
        ini = 0
        fin = len(nums)-1
        if(nums[ini]==target):
            return ini
        elif(nums[fin]==target):
            return fin
        
        ant = 0
        ant2 = ini
        ant3 = fin
        m=0
        while ini < fin:
            m = (fin+ini)//2
            print(ini,fin,m)
            if(nums[m]==target or nums[ini]== target or nums[fin]==target):
                break
            if(target>nums[ini] and target<nums[m]):
                fin = m
            elif(target>nums[m] and target<nums[fin]):
                ini = m
            else:
                ini += 1
                fin -= 1
            
            if(ant2 == ini and ant3 == fin):
                break

            ant = m
            ant2 = ini
            ant3 = fin
        if(nums[m]==target):
            return m
        elif(nums[ini]==target):
            return ini
        elif(nums[fin]==target):
            return fin
        else:
            return -1
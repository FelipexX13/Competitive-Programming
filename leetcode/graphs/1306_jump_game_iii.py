class Solution:
    
    def numeri(self, nums, start, l, tam):

        if(start in l):
            return False

        l.add(start)

        pos1 = start + nums[start]
        pos2 = start - nums[start]

        val1, val2 = False, False

        if(pos1 < tam and nums[pos1] == 0):
            return True
        else:
            if(pos1 < tam):
                val1 = self.numeri(nums, pos1, l, tam)

        if(pos2 > -1 and nums[pos2] == 0):
            return True
        else:
            if(pos2 >= 0):
                val2 = self.numeri(nums, pos2, l, tam)

        return val1 or val2


    def canReach(self, arr: List[int], start: int) -> bool:

        tam = len(arr)

        if(0 not in arr):
            return False

        elif(arr[start] == 0):
            return True

        else:
            l = set()
            a = self.numeri(arr, start, l, tam)
            return a
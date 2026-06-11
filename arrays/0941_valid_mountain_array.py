class Solution:
    def validMountainArray(self, arr: List[int]) -> bool:
        subiendo = True
        if len(arr) < 3:
            return False
        if arr[0] > arr[1]:
            return False
        for i in range(1, len(arr)):
            diff = arr[i] - arr[i-1]
            if diff == 0:
                return False
            elif subiendo and diff < 0:
                subiendo = False
            elif not subiendo and diff > 0:
                return False
        if subiendo:
            return False
        return True
                
                
            

                
            
        
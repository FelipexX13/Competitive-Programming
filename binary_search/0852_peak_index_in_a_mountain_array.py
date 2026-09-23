class Solution:
    def peakIndexInMountainArray(self, arr: List[int]) -> int:
        ini = 0
        fin = len(arr)-1
        while ini < fin:
            mitad = (ini+fin)//2
            if(arr[mitad]>arr[mitad+1]):
                fin = mitad
            if(arr[mitad]>arr[mitad-1]):
                ini = mitad
        return mitad
            

        
class Solution:
    def minimumAbsDifference(self, arr: List[int]) -> List[List[int]]:
        a = sorted(arr)
        mi = float("inf")
        for i in range(1,len(arr)):
            if(a[i]-a[i-1] < mi):
                mi = a[i]-a[i-1]
        
        fin = []
        for i in range(1,len(arr)):
            if(a[i]-a[i-1] == mi):
                fin.append([a[i-1], a[i]])
        return fin

        
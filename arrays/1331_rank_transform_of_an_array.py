class Solution:
    def arrayRankTransform(self, arr: List[int]) -> List[int]:
        k = sorted(list(set(arr)))
        dic = {}
        
        for i in range(len(k)):
            dic[k[i]] = i+1
        f = []
        for i in range(len(arr)):
            f.append(dic[arr[i]])
        return f
         
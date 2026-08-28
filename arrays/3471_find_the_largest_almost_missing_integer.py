class Solution:
    def largestInteger(self, nums: List[int], k: int) -> int:
        lista = {}
        i = 0
        while i<(len(nums)-k+1):
            ka = list(set(nums[i:i+k]))
            for j in ka:
                if(j in lista):
                    lista[j]+=1
                else:
                    lista[j]=1
            i+=1
        unicos = []
        for clave,valor in lista.items():
            if(valor == 1):
                unicos.append(clave)
        if(len(unicos)==0):
            return -1
        return max(unicos)
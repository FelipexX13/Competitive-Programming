class Solution:
    def minSubarray(self, nums: List[int], p: int) -> int:
        j = sum(nums) 
        f = j % p
        if(j%p == 0):
            return 0
        dic = {0: -1} #esto es que ya encontro
        suma = 0
        g = []
        for pos in range(len(nums)):
            actual = nums[pos]
            suma += actual%p
            suma %= p #voy mirando cuanto me aporta cada numero
            
            n = (suma - f)%p #Esta ecuación me dice cuanto hace falta para poder eliminarlo
            if(n in dic):
                longitud = pos - dic[n] 
                if longitud < len(nums): #El ejercicio dice que no puedo quitar todos los numeros
                    g.append(longitud)
            dic[suma] = pos
        
        if(len(g) == 0):
            return -1
        return min(g)

            

        
        
        
        
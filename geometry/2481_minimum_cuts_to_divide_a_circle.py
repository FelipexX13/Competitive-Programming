class Solution:
    def numberOfCuts(self, n: int) -> int:
        pedazos = n

        if (pedazos % 2) == 0:
            
            trazos = pedazos/2
            
        elif pedazos == 1:
            
            trazos = 0
            
        else:
            
            trazos = pedazos
            
            
        return(int(trazos))
        
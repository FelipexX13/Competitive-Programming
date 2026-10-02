# <3
# Tema: LeetCode Hub / Agrupar Rangos Consecutivos
# Resumen: Barrer y cortar cada vez que el siguiente no es el actual mas 1
# O: (n), un solo barrido
# Detalle: LeetCode 228 "Summary Ranges": resumir un arreglo ordenado en rangos como "0->2".
# Tecnica: barrer y cortar cada vez que el siguiente no es el actual mas 1. El try/except es lo
# que maneja el final del arreglo, donde nums[i+1] se sale. Depender del except para cerrar el
# ultimo rango es fragil; queda mas claro con un for hasta n-1 y el cierre afuera del ciclo.

class Solution:
    def summaryRanges(self, nums: List[int]) -> List[str]:
        


        resultado = []

        if len(nums) == 0:
            
            return ([])
            
        else:
            
            a = nums[0]

            try:

                for i in range(len(nums)):
                    
                    b = nums[i + 1]

                    if b == nums[i] + 1:
                        
                        continue
                    
                    else:
                        
                        if a == nums[i]:
                            
                            resultado.append(str(a))
                            
                        else:
                            
                            resultado.append(f"{a}->{nums[i]}")
                            
                        a = b
                        
            except:
                
                if a == nums[-1]:
                        
                    resultado.append(str(a))
                    
                else:
                    
                    resultado.append(f"{a}->{nums[-1]}")
                    
                
                return (resultado)

# <3
# Tema: LeetCode Hub / Busqueda en Arreglo Rotado
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (log n)
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 153 "Find Minimum in Rotated Sorted Array": el minimo de un ordenado y rotado.
# Tecnica: binaria comparando el medio contra los extremos. Si nums[ini] > nums[m] el punto de
# rotacion esta a la izquierda; si nums[fin] < nums[m] esta a la derecha; si no hay desorden el
# trozo ya esta ordenado y el minimo es nums[ini]. La version canonica es mas corta: while ini <
# fin, si nums[m] > nums[fin] entonces ini = m+1, si no fin = m; al salir nums[ini] es el
# minimo.

class Solution:
    def findMin(self, nums: List[int]) -> int:
        n = len(nums)
        ini = 0
        fin = n-1
        while (ini<fin):
            m = (fin+ini)//2
            if(nums[ini]>nums[m]):
                fin = m
            elif(nums[fin]<nums[m]):
                ini = m
            else:
                break
                
            if(fin-ini==1):
                break
        if(nums[ini] > nums[fin]):
            return (nums[fin])
        else:
            return(nums[ini])
            
            
        
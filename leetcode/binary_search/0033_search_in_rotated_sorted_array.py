# <3
# Tema: LeetCode Hub / Busqueda en Arreglo Rotado
# Resumen: Buscar un valor en un arreglo ordenado que fue rotado
# O: (n) en el peor caso por el ini+=1/fin-=1; la binaria limpia es (log n)
# Detalle: LeetCode 33 "Search in Rotated Sorted Array": buscar un valor en un arreglo ordenado
# que fue rotado. Tecnica del codigo: binaria con casos, y cuando no puede decidir de que lado
# esta el objetivo encoge los dos extremos de uno en uno. OJO: ese ini += 1 / fin -= 1 hace que
# en el peor caso sea O(n), no O(log n). Ademas deja un print adentro del ciclo. La forma
# limpia: mirar si nums[ini] <= nums[m] para saber cual mitad esta ordenada, y ahi decidir con
# un solo if.

class Solution:
    def search(self, nums: List[int], target: int) -> int:
        ini = 0
        fin = len(nums)-1
        if(nums[ini]==target):
            return ini
        elif(nums[fin]==target):
            return fin
        
        ant = 0
        ant2 = ini
        ant3 = fin
        m=0
        while ini < fin:
            m = (fin+ini)//2
            print(ini,fin,m)
            if(nums[m]==target or nums[ini]== target or nums[fin]==target):
                break
            if(target>nums[ini] and target<nums[m]):
                fin = m
            elif(target>nums[m] and target<nums[fin]):
                ini = m
            else:
                ini += 1
                fin -= 1
            
            if(ant2 == ini and ant3 == fin):
                break

            ant = m
            ant2 = ini
            ant3 = fin
        if(nums[m]==target):
            return m
        elif(nums[ini]==target):
            return ini
        elif(nums[fin]==target):
            return fin
        else:
            return -1
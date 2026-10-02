# <3
# Tema: LeetCode Hub / Busqueda Lineal
# Resumen: Donde esta el target, o donde habria que insertarlo
# O: (n) lineal; el problema pide O(log n) con binaria
# Detalle: LeetCode 35 "Search Insert Position": donde esta el target, o donde habria que
# insertarlo. Tecnica: recorrer hasta el primer valor mayor o igual. Es O(n). El problema pide
# O(log n): es binaria, y este es justo el lower_bound de C++. Vale la pena hacerlo con binaria
# porque es el esqueleto que despues se usa para todo.

class Solution:
    def searchInsert(self, nums: List[int], target: int) -> int:
        for i in range(len(nums)):
            if(nums[i]==target or nums[i]>target):
                return i
        return len(nums)
        
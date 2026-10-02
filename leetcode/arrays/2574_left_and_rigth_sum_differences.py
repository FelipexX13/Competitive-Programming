# <3
# Tema: LeetCode Hub / Sumas a Izquierda y Derecha
# Resumen: Para cada posicion, el valor absoluto de la suma de lo que hay a su izquierda menos lo de su derecha
# O: (n^2) por el sum() de cada posicion; con prefijos seria (n)
# Detalle: LeetCode 2574 "Left and Right Sum Differences": para cada posicion, el valor absoluto
# de la suma de lo que hay a su izquierda menos lo de su derecha. Tecnica: sum() de los dos
# pedazos en cada posicion, o sea O(n^2). Con sumas de prefijos es O(n): la izquierda es pref[i]
# y la derecha es total - pref[i+1]. Es el ejemplo mas simple de para que sirven los prefijos.

class Solution:
    def leftRightDifference(self, nums: List[int]) -> List[int]:
        f = []
        for i in range(len(nums)):
            ll = sum(nums[0:i])
            rr = sum(nums[i+1:len(nums)])
            f.append(abs(ll-rr))
        return f
        
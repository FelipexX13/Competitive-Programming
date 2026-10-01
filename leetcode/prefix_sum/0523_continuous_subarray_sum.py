# <3
# Tema: LeetCode Hub / Residuos de Prefijos
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n), residuo de prefijo -> primera posicion
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 523 "Continuous Subarray Sum": decir si hay un subarreglo de largo al menos 2 con
# suma multiplo de k. Tecnica: la suma de [i+1..j] es multiplo de k si los prefijos i y j dejan
# el MISMO residuo. Se guarda en un diccionario el residuo -> primera posicion donde aparecio, y
# se exige que la distancia sea al menos 2. El dic arranca con {0: -1} para cubrir el prefijo
# vacio. Guardar solo la PRIMERA aparicion es lo que maximiza la distancia.

class Solution:
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        if(len(nums)==1):
            return False
        dic = {0: -1}
        res = 0
        ini = 0
        for i in range(len(nums)):
            ini += nums[i]
            res = ini%k
            if(res not in dic):
                dic[res] = i
            else:
                if i - dic[res] >= 2:
                    return True
        return False
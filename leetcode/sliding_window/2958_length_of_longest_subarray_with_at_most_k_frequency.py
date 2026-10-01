# <3
# Tema: LeetCode Hub / Ventana con Frecuencias
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n), ventana con diccionario de frecuencias
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 2958 "Length of Longest Subarray With at Most K Frequency": el subarreglo mas largo
# donde ningun valor aparece mas de k veces. Tecnica: ventana deslizante con diccionario de
# frecuencias. Cuando un valor llega a k+1 se encoge por la izquierda hasta que deje de pasarse.
# La bandera f es para no volver a contar el elemento de la derecha mientras la ventana se
# encoge; con el patron normal (un while adentro del for) no hace falta.

class Solution:
    def maxSubarrayLength(self, nums: List[int], k: int) -> int:
        ini = 0
        fin = 1
        dic = {nums[ini]: 1}
        cap = []
        f = True
        while fin < len(nums):
            if(nums[fin] in dic and f):
                dic[nums[fin]] += 1
            elif(f):
                dic[nums[fin]] = 1
            if dic[nums[fin]] == (k+1):
                cap.append(fin-ini)
                dic[nums[ini]] -= 1
                ini += 1
                f = False
            else:
                fin+=1
                f = True
        cap.append(fin-ini)
        return max(cap)
        
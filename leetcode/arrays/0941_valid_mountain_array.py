# <3
# Tema: LeetCode Hub / Verificar Sube y Baja
# Resumen: Decir si el arreglo sube estrictamente y luego baja estrictamente
# O: (n), un barrido con una bandera
# Detalle: LeetCode 941 "Valid Mountain Array": decir si el arreglo sube estrictamente y luego
# baja estrictamente. Tecnica: una bandera subiendo que solo puede cambiar una vez. Si vuelve a
# subir despues de haber bajado, no es montana; si alguna diferencia es 0, tampoco (tiene que
# ser estricto). Los casos que hay que cuidar son los que el codigo pone al inicio y al final:
# menos de 3 elementos, y que nunca haya bajado.

class Solution:
    def validMountainArray(self, arr: List[int]) -> bool:
        subiendo = True
        if len(arr) < 3:
            return False
        if arr[0] > arr[1]:
            return False
        for i in range(1, len(arr)):
            diff = arr[i] - arr[i-1]
            if diff == 0:
                return False
            elif subiendo and diff < 0:
                subiendo = False
            elif not subiendo and diff > 0:
                return False
        if subiendo:
            return False
        return True
                
                
            

                
            
        
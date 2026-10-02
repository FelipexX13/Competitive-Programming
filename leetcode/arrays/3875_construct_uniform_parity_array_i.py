# <3
# Tema: LeetCode Hub / Paridad por Fuerza Bruta
# Resumen: Decir si se puede dejar todo el arreglo con la misma paridad usando restas entre elementos
# O: (n^2), todos los pares
# Detalle: LeetCode 3875 "Construct Uniform Parity Array I": decir si se puede dejar todo el
# arreglo con la misma paridad usando restas entre elementos. Tecnica: por cada elemento busca
# otro con el que la resta cambie su paridad, y cuenta cuantos pueden quedar pares y cuantos
# impares. Es O(n^2). Lo que importa es que par - impar es impar y par - par es par: la paridad
# del resultado sale de la paridad de los dos operandos, nada mas. La version II usa eso para
# bajar a O(n).

class Solution:
    def uniformArray(self, nums1: list[int]) -> bool:
        lPar = []
        lImpar = []
        for i in range(len(nums1)):
            if(nums1[i]%2==0):
                lPar.append(nums1[i])
                for j in range(len(nums1)):
                    if(i!=j and (nums1[i]-nums1[j])%2==1):
                        lImpar.append(nums1[i]-nums1[j])
                        break
            else:
                lImpar.append(nums1[i])
                for j in range(len(nums1)):
                    if(i!=j and (nums1[i]-nums1[j])%2==0):
                        lPar.append(nums1[i]-nums1[j])
                        break
        
        if(len(lPar)== len(nums1) or len(lImpar)==len(nums1)):
            return True
        else:
            return False
        
# <3
# Tema: LeetCode Hub / Buscar el Primer Multiplo Ausente
# Resumen: El menor multiplo de k que no esta en el arreglo
# O: (respuesta): prueba todos los enteros y filtra por k
# Detalle: LeetCode 3718 "Smallest Missing Multiple of K": el menor multiplo de k que no esta en
# el arreglo. Tecnica: set con los valores y probar k, 2k, 3k, ... hasta que falte uno. El ciclo
# prueba todos los enteros y filtra con m % k == 0; saltando de k en k daria lo mismo y k veces
# mas rapido.

class Solution:
    def missingMultiple(self, nums: List[int], k: int) -> int:
        t = set(nums)
        m = 1
        while True:
            if(m%k==0 and m not in t):
                return m
            m+=1
        
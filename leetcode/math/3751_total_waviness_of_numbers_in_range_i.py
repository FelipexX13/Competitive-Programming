# <3
# Tema: LeetCode Hub / Fuerza Bruta sobre Digitos
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (rango * digitos); la version II pide digit DP
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 3751 "Total Waviness of Numbers in Range I": contar los picos y valles de los digitos
# de todos los numeros del rango. Tecnica: recorrer el rango entero y en cada numero mirar las
# ternas de digitos consecutivos: es pico si el del medio es mayor que sus dos vecinos, valle si
# es menor. Es la version I, con rango chico. La II pediria digit DP, o sea contar por posicion
# en vez de recorrer numero por numero.

class Solution:
    def totalWaviness(self, num1: int, num2: int) -> int:
        cont=0
        for i in range(num1,num2+1,1):
            a = str(i)
            for j in range(1,len(a)-1,1):
                if(a[j-1]< a[j] and a[j+1] < a[j]):
                    cont+=1
                elif(a[j-1]> a[j] and a[j+1] > a[j]):
                    cont+=1
        return cont
        
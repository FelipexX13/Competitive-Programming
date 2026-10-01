# <3
# Tema: LeetCode Hub / Conteo por Bandas de Magnitud
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (log n), bajando potencia de 10 por potencia de 10
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 3871 "Count Commas in Range II": la misma cuenta de comas, pero con rangos grandes.
# Tecnica: bajar por bandas. Se toma la potencia de 10 mas cercana por debajo de n, se cuenta
# cuantos numeros hay de ahi a n (todos con la misma cantidad de comas, (digitos-1)//3), se suma
# y se repite con n = potencia - 1 hasta llegar por debajo de 1000. Ese partir el rango en
# tramos donde la respuesta es constante es la idea reutilizable.

class Solution:
    def countCommas(self, n: int) -> int:
        cont = 0
        num = int("1"+("0"*(len(str(n))-1)))
        while num > 999:
            div = (len(str(num))-1)//3
            cont+=(n-num+1)*div
            n=num-1
            num = int("1"+("0"*(len(str(num))-2)))
        return cont
        
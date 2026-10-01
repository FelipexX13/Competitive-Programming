# <3
# Tema: LeetCode Hub / Manejo de Digitos
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 3754 "Concatenate Non-Zero Digits and Multiply by Sum I": pegar los digitos que no
# son 0 y multiplicar ese numero por la suma de sus digitos. Tecnica: armar el string sin ceros,
# sumar los digitos y multiplicar. El try/except cubre el caso de que no quede ningun digito (n
# era todo ceros), donde int('') falla.

class Solution:
    def sumAndMultiply(self, n: int) -> int:
        h = ""
        j = str(n)
        for i in j:
            if(i!="0"):
                h+=i
        sums = 0
        for i in h:
            sums+=int(i)
        try:
            return int(h)*sums
        except:
            return 0
        
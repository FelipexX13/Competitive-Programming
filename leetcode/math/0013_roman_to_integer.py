# <3
# Tema: LeetCode Hub / Numeros Romanos
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 13 "Roman to Integer": convertir un numero romano a entero.
# Tecnica: dos diccionarios, uno de simbolos sueltos y otro de los seis pares restadores (IV,
# IX, XL, XC, CD, CM). Primero se consumen los pares y despues se suma lo que sobro.
# La forma clasica es un solo barrido: si el valor actual es menor que el siguiente, se resta.
# Sale mas corto y no hace falta el segundo diccionario.

class Solution:
    def romanToInt(self, s: str) -> int:
        dic = {"I":1, "V":5,"X":10,"L":50,"C":100, "D":500, "M":1000}
        dic2 = {"IV":4, "IX":9,"XL":40,"XC":90,"CD":400, "CM":900}
        s = list(s)
        i = 0
        cont = 0
        while i < len(s):
            try:
                su = str(s[i])+str(s[i+1])
                cont +=dic2[su]
                s.pop(i+1)
                s.pop(i)
                continue
            except:
                a=0
            i+=1
        for i in s:
            cont+=dic[i]
        return cont
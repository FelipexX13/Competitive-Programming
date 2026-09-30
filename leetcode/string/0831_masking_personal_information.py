# <3
# Tema: LeetCode Hub / Enmascarar por Formato
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 831 "Masking Personal Information": tapar un correo o un telefono segun reglas fijas.
# Tecnica: primero decide si es telefono o correo intentando convertir el ultimo caracter a
# entero; si falla, es correo. Para el telefono se sacan solo los digitos y el prefijo de asteriscos
# depende de cuantos queden (10, 11, 12 o 13). Para el correo se deja la primera letra, cinco
# asteriscos, la ultima letra del nombre y el dominio en minusculas.
# Es puro manejo de casos; lo que se lleva uno es la idea de detectar el formato por el ultimo
# caracter en vez de buscar la arroba.

class Solution:
    def maskPII(self, s: str) -> str:
        #NUMERO
        try:
            for i in range(len(s)-1,-1,-1):
                if(s[i]!="-" and s[i]!= " "):
                    break
            f = int(s[i])
            nums = ""
            for i in s:
                try:
                    a = int(i)
                    nums += i
                except:
                    continue
            tam = len(nums)
            if(tam == 10):
                return "***-***-"+nums[len(nums)-4:len(nums)]
            elif(tam == 11):
                return "+*-***-***-"+nums[len(nums)-4:len(nums)]
            elif(tam == 12):
                return "+**-***-***-"+nums[len(nums)-4:len(nums)]
            else:
                return "+***-***-***-"+nums[len(nums)-4:len(nums)]
            
        #CORREO
        except:
            ini = s[0].lower()
            f = ""
            ya = False
            correo = ""
            for i in range(len(s)):
                if(s[i] == "@" ):
                    ya = True
                if(s[i] != "@" and ya == False):
                    try:
                        f = s[i].lower()
                    except:
                        f = s[i]
                elif(s[i] == "@" and f != ""):
                    correo = s[i:len(s)]
                    break
            g = ""
            for i in correo:
                try:
                    g += i.lower()
                except:
                    g += i
            c = ini + "*****" + f + g
            return c
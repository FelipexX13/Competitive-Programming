# <3
# Tema: LeetCode Hub / Agrupar de Atras hacia Adelante
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 482 "License Key Formatting": reagrupar la llave en bloques de k separados por guion,
# donde solo el PRIMER grupo puede ser mas corto. Tecnica: como el grupo corto queda al inicio,
# primero se cuenta cuantos caracteres utiles hay y se saca el residuo modulo k; ese residuo es
# el tamano del primer bloque. Despues los demas van de k en k. Sale mas limpio construyendo el
# resultado al REVES de a k y volteandolo al final.

class Solution:
    def licenseKeyFormatting(self, s: str, k: int) -> str:
        c = 0
        for i in s:
            if(i != "-"):
                c+=1
        cant = c%k
        fin = ""
        if(cant!= 0):
            c = 0
            voy = 0
            for i in range(len(s)):
                if(s[i] != "-"):
                    try:
                        fin += s[i].upper()
                    except:
                        fin += s[i]
                    c+=1
                voy = i
                if(c==cant):
                    fin+="-"
                    break
        else:
            c = 0
            voy = 0
            for i in range(len(s)):
                if(s[i] != "-"):
                    try:
                        fin += s[i].upper()
                    except:
                        fin += s[i]
                    c+=1
                voy = i
                if(c==k):
                    fin+="-"
                    break
        c = 0
        for i in range(voy+1, len(s)):
            if(s[i] != "-"):
                try:
                    fin += s[i].upper()
                except:
                    fin += s[i]
                c+=1
            if(c==k):
                fin += "-"
                c = 0
        try:
            if(fin[-1]== "-"):
                return fin[0:-1]
            else:
                return fin
        except:
            return fin
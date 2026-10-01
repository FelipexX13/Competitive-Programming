# <3
# Tema: LeetCode Hub / Conteo por Magnitud
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 3870 "Count Commas in Range I": cuantas comas de separador de miles se escriben en
# total al listar los numeros hasta n. Tecnica: la cantidad de comas de un numero depende solo
# de cuantos digitos tiene (una cada tres digitos). El ciclo cuenta cuantos grupos de tres tiene
# n y multiplica por cuantos numeros hay desde 1000. OJO: es la version I, donde todos los
# numeros del rango caben en la misma banda de magnitud. Cuando el rango cruza varias bandas hay
# que sumar banda por banda, y eso es el 3871.

class Solution:
    def countCommas(self, n: int) -> int:
        if(len(str(n))<=3):
            return 0
        else:
            k = 1000
            c = 1
            ja = 0
            while True:
                if(n//k == 0):
                    break
                if(ja==3):
                    c+=1
                    ja = 0
                k*=10
                ja+=1
            k=1000
            return int(n-k+1)*c

            
        
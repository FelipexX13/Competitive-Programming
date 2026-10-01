# <3
# Tema: LeetCode Hub / Casos por Paridad
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (1), tres casos por paridad
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 2481 "Minimum Cuts to Divide a Circle": cortes minimos para partir un circulo en n
# pedazos iguales. Tecnica: cada corte es un DIAMETRO y parte el circulo en dos, asi que con n
# par bastan n/2. Con n impar los diametros no sirven y toca n. Y con n = 1 no se corta nada.

class Solution:
    def numberOfCuts(self, n: int) -> int:
        pedazos = n

        if (pedazos % 2) == 0:
            
            trazos = pedazos/2
            
        elif pedazos == 1:
            
            trazos = 0
            
        else:
            
            trazos = pedazos
            
            
        return(int(trazos))
        
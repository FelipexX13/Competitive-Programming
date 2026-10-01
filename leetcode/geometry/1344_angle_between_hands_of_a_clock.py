# <3
# Tema: LeetCode Hub / Angulos de un Reloj
# Resumen: NO ES MIO: codigo de Stiven Correa, del repo del equipo (carpeta leetcode/)
#
# O: (1)
# Detalle: NO ES MIO: codigo de Stiven Correa, del repo del equipo (carpeta leetcode/). LeetCode
# 1344 "Angle Between Hands of a Clock": angulo menor entre las manecillas. Tecnica: el minutero
# avanza 6 grados por minuto; la hora avanza 30 grados por hora PERO tambien se mueve con los
# minutos, de ahi el (hour + minutes/60). Al final se toma el menor entre la diferencia y 360
# menos la diferencia.

class Solution:
    def angleClock(self, hour: int, minutes: int) -> float:
        minAng = (360/60)*minutes
        hourAng = ((360/12)*((hour+minutes/60)%24))%360

        return min(abs(minAng-hourAng),abs(hourAng-minAng), 360-abs(minAng-hourAng), 360-abs(hourAng-minAng))
